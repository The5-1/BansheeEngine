#include "$ENGINE$\DeferredLightCommon.bslinc"

technique DeferredDirectionalLight
{
	mixin DeferredLightCommon;

	depth
	{
		read = false;
	};
	
	#ifdef MSAA
	stencil
	{
		enabled = true;
		front = { keep, keep, keep, eq };
		readmask = 0x80;
		
		#ifdef MSAA_RESOLVE_0TH
		reference = 0;
		#else
		reference = 0x80;
		#endif
	};
	#endif
	
	code 
	{
		#ifndef MSAA_RESOLVE_0TH
			#define MSAA_RESOLVE_0TH 0
		#endif	
	
		struct VStoFS
		{
			float4 position : SV_POSITION;
			float2 uv0 : TEXCOORD0;
			float3 screenDir : TEXCOORD1;
		};

		struct VertexInput
		{
			float2 screenPos : POSITION;
			float2 uv0 : TEXCOORD0;
		};
		
		VStoFS vsmain(VertexInput input)
		{
			VStoFS output;
		
			output.position = float4(input.screenPos, 0, 1);
			output.uv0 = input.uv0;
			output.screenDir = mul(gMatInvProj, float4(input.screenPos, 1, 0)).xyz - gViewOrigin.xyz;
		
			return output;
		}

		float4 fsmain(VStoFS input
			#if MSAA_COUNT > 1 && !MSAA_RESOLVE_0TH
			, uint sampleIdx : SV_SampleIndex
			#endif
			) : SV_Target0
		{
			uint2 pixelPos = (uint2)(input.uv0 * (float2)gViewportRectangle.zw - ((float2)gViewportRectangle.xy + 0.5f));
			
			#if MSAA_COUNT > 1
				#if MSAA_RESOLVE_0TH
					SurfaceData surfaceData = getGBufferData(pixelPos, 0);
				#else
					SurfaceData surfaceData = getGBufferData(pixelPos, sampleIdx);
				#endif
			#else
			SurfaceData surfaceData = getGBufferData(pixelPos);
			#endif			
		
			if(surfaceData.worldNormal.w > 0.0f)
			{
				float3 cameraDir = normalize(input.screenDir);
				float3 worldPosition = input.screenDir * surfaceData.depth + gViewOrigin;
				
				float3 V = normalize(gViewOrigin - worldPosition);
				float3 N = surfaceData.worldNormal.xyz;
				float3 R = 2 * dot(V, N) * N - V;

				float roughness2 = max(surfaceData.roughness, 0.08f);
				roughness2 *= roughness2;
				
				LightData lightData = getLightData();
				
				#if MSAA_COUNT > 1
					#if MSAA_RESOLVE_0TH
						float occlusion = gLightOcclusionTex.Load(pixelPos, 0).r;
					#else
						float occlusion = gLightOcclusionTex.Load(pixelPos, sampleIdx).r;
					#endif
				#else
				float occlusion = gLightOcclusionTex.Load(int3(pixelPos, 0)).r;
				#endif
				
				// Reverse the sqrt we did when storing it
				occlusion *= occlusion;
				
				occlusion = 1.0f - occlusion;
				
				return float4(getLuminanceDirectional(lightData, worldPosition, V, R, surfaceData) * occlusion, 1.0f);
			}
			else
				return float4(0.0f, 0.0f, 0.0f, 0.0f);
		}
	};
};