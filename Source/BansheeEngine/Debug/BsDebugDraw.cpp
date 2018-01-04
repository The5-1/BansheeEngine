//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#include "Debug/BsDebugDraw.h"
#include "Mesh/BsMesh.h"
#include "RenderAPI/BsVertexDataDesc.h"
#include "Utility/BsShapeMeshes3D.h"
#include "Mesh/BsMeshHeap.h"
#include "2D/BsSpriteTexture.h"
#include "CoreThread/BsCoreThread.h"
#include "Material/BsMaterial.h"
#include "RenderAPI/BsGpuParams.h"
#include "Material/BsGpuParamsSet.h"
#include "RenderAPI/BsRenderAPI.h"
#include "Renderer/BsRenderer.h"
#include "Renderer/BsRendererUtility.h"
#include "Mesh/BsTransientMesh.h"
#include "Utility/BsDrawHelper.h"
#include "Renderer/BsRendererExtension.h"
#include "Resources/BsBuiltinResources.h"
#include "Renderer/BsCamera.h"

using namespace std::placeholders;

namespace bs
{
	DebugDraw::DebugDraw()
		: mDrawHelper(nullptr)
	{
		mDrawHelper = bs_new<DrawHelper>();
		mRenderer = RendererExtension::create<ct::DebugDrawRenderer>(nullptr);
	}

	DebugDraw::~DebugDraw()
	{
		mDrawHelper->clearMeshes(mActiveMeshes);
		mActiveMeshes.clear();

		bs_delete(mDrawHelper);
	}

	void DebugDraw::setColor(const Color& color)
	{
		mDrawHelper->setColor(color);
	}

	void DebugDraw::setTransform(const Matrix4& transform)
	{
		mDrawHelper->setTransform(transform);
	}

	void DebugDraw::drawCube(const Vector3& position, const Vector3& extents)
	{
		mDrawHelper->cube(position, extents);
	}

	void DebugDraw::drawSphere(const Vector3& position, float radius)
	{
		mDrawHelper->sphere(position, radius);
	}

	void DebugDraw::drawCone(const Vector3& base, const Vector3& normal, float height, float radius, const Vector2& scale)
	{
		mDrawHelper->cone(base, normal, height, radius, scale);
	}

	void DebugDraw::drawDisc(const Vector3& position, const Vector3& normal, float radius)
	{
		mDrawHelper->disc(position, normal, radius);
	}

	void DebugDraw::drawWireCube(const Vector3& position, const Vector3& extents)
	{
		mDrawHelper->wireCube(position, extents);
	}

	void DebugDraw::drawWireSphere(const Vector3& position, float radius)
	{
		mDrawHelper->wireSphere(position, radius);
	}

	void DebugDraw::drawWireCone(const Vector3& base, const Vector3& normal, float height, float radius, const Vector2& scale)
	{
		mDrawHelper->wireCone(base, normal, height, radius, scale);
	}

	void DebugDraw::drawLine(const Vector3& start, const Vector3& end)
	{
		mDrawHelper->line(start, end);
	}

	void DebugDraw::drawLineList(const Vector<Vector3>& linePoints)
	{
		mDrawHelper->lineList(linePoints);
	}

	void DebugDraw::drawWireDisc(const Vector3& position, const Vector3& normal, float radius)
	{
		mDrawHelper->wireDisc(position, normal, radius);
	}

	void DebugDraw::drawWireArc(const Vector3& position, const Vector3& normal, float radius, 
		Degree startAngle, Degree amountAngle)
	{
		mDrawHelper->wireArc(position, normal, radius, startAngle, amountAngle);
	}

	void DebugDraw::drawWireMesh(const SPtr<MeshData>& meshData)
	{
		mDrawHelper->wireMesh(meshData);
	}

	void DebugDraw::drawFrustum(const Vector3& position, float aspect, Degree FOV, float near, float far)
	{
		mDrawHelper->frustum(position, aspect, FOV, near, far);
	}

	Vector<DebugDraw::MeshRenderData> DebugDraw::createMeshProxyData(const Vector<DrawHelper::ShapeMeshData>& meshData)
	{
		Vector<MeshRenderData> proxyData;
		for (auto& entry : meshData)
		{
			if (entry.type == DrawHelper::MeshType::Solid)
				proxyData.push_back(MeshRenderData(entry.mesh->getCore(), DebugDrawMaterial::Solid));
			else if (entry.type == DrawHelper::MeshType::Wire)
				proxyData.push_back(MeshRenderData(entry.mesh->getCore(), DebugDrawMaterial::Wire));
			else if (entry.type == DrawHelper::MeshType::Line)
				proxyData.push_back(MeshRenderData(entry.mesh->getCore(), DebugDrawMaterial::Line));
		}

		return proxyData;
	}

	void DebugDraw::clear()
	{
		mDrawHelper->clear();
	}

	void DebugDraw::_update()
	{
		mDrawHelper->clearMeshes(mActiveMeshes);
		mActiveMeshes.clear();

		mDrawHelper->buildMeshes(DrawHelper::SortType::None, Vector3::ZERO);
		mActiveMeshes = mDrawHelper->getMeshes();

		Vector<MeshRenderData> proxyData = createMeshProxyData(mActiveMeshes);

		ct::DebugDrawRenderer* renderer = mRenderer.get();
		gCoreThread().queueCommand(std::bind(&ct::DebugDrawRenderer::updateData, renderer, proxyData));
	}

	namespace ct
	{

	DebugDrawParamsDef gDebugDrawParamsDef;

	ShaderVariation DebugDrawMat::VAR_Solid = ShaderVariation({
		ShaderVariation::Param("SOLID", true)
	});

	ShaderVariation DebugDrawMat::VAR_Line = ShaderVariation({
		ShaderVariation::Param("LINE", true)
	});

	ShaderVariation DebugDrawMat::VAR_Wire = ShaderVariation({
		ShaderVariation::Param("WIRE", true)
	});

	DebugDrawMat::DebugDrawMat()
	{
		// Do nothing
	}

	void DebugDrawMat::_initVariations(ShaderVariations& variations)
	{
		variations.add(VAR_Solid);
		variations.add(VAR_Line);
		variations.add(VAR_Wire);
	}

	void DebugDrawMat::execute(const SPtr<GpuParamBlockBuffer>& params, const SPtr<MeshBase>& mesh)
	{
		mParamsSet->setParamBlockBuffer("Params", params);

		gRendererUtility().setPass(mMaterial);
		gRendererUtility().setPassParams(mParamsSet);
		gRendererUtility().draw(mesh);
	}

	DebugDrawMat* DebugDrawMat::getVariation(DebugDrawMaterial mat)
	{
		if (mat == DebugDrawMaterial::Solid)
			return get(VAR_Solid);
		
		if (mat == DebugDrawMaterial::Wire)
			return get(VAR_Wire);

		return get(VAR_Line);
	}

	DebugDrawRenderer::DebugDrawRenderer()
		:RendererExtension(RenderLocation::PostLightPass, 0)
	{
	}

	void DebugDrawRenderer::initialize(const Any& data)
	{
		THROW_IF_NOT_CORE_THREAD;

		mParamBuffer = gDebugDrawParamsDef.createBuffer();
	}

	void DebugDrawRenderer::updateData(const Vector<DebugDraw::MeshRenderData>& meshes)
	{
		mMeshes = meshes;
	}

	bool DebugDrawRenderer::check(const Camera& camera)
	{
		return true;
	}

	void DebugDrawRenderer::render(const Camera& camera)
	{
		SPtr<RenderTarget> renderTarget = camera.getViewport()->getTarget();
		if (renderTarget == nullptr)
			return;

		Matrix4 viewMatrix = camera.getViewMatrix();
		Matrix4 projMatrix = camera.getProjectionMatrixRS();
		Matrix4 viewProjMat = projMatrix * viewMatrix;

		gDebugDrawParamsDef.gMatViewProj.set(mParamBuffer, viewProjMat);
		gDebugDrawParamsDef.gViewDir.set(mParamBuffer, (Vector4)camera.getTransform().getForward());

		for (auto& entry : mMeshes)
		{
			DebugDrawMat* mat = DebugDrawMat::getVariation(entry.type);
			mat->execute(mParamBuffer, entry.mesh);
		}
	}
	}
}
