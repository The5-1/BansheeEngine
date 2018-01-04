//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#pragma once

#include "BsD3D11Prerequisites.h"
#include "RenderAPI/BsRenderWindow.h"

namespace bs { 
	/** @addtogroup D3D11
	 *  @{
	 */

	/**
	 * Render window implementation for Windows and DirectX 11.
	 *
	 * @note	Sim thread only.
	 */
	class D3D11RenderWindow : public RenderWindow
	{
	public:
		~D3D11RenderWindow() { }

		/** @copydoc RenderWindow::screenToWindowPos */
		void getCustomAttribute(const String& name, void* pData) const override;

		/** @copydoc RenderWindow::screenToWindowPos */
		Vector2I screenToWindowPos(const Vector2I& screenPos) const override;

		/** @copydoc RenderWindow::windowToScreenPos */
		Vector2I windowToScreenPos(const Vector2I& windowPos) const override;

		/** @copydoc RenderWindow::getCore */
		SPtr<ct::D3D11RenderWindow> getCore() const;

	protected:
		friend class D3D11RenderWindowManager;
		friend class ct::D3D11RenderWindow;

		D3D11RenderWindow(const RENDER_WINDOW_DESC& desc, UINT32 windowId, 
			ct::D3D11Device& device, IDXGIFactory* DXGIFactory);

		/** @copydoc RenderWindow::getProperties */
		const RenderTargetProperties& getPropertiesInternal() const override { return mProperties; }

		/** @copydoc RenderWindow::syncProperties */
		void syncProperties() override;

		/**	Retrieves internal window handle. */
		HWND getHWnd() const;

	private:
		ct::D3D11Device& mDevice;
		IDXGIFactory* mDXGIFactory;
		RenderWindowProperties mProperties;
	};

	namespace ct
	{
	/**
	 * Render window implementation for Windows and DirectX 11.
	 *
	 * @note	Core thread only.
	 */
	class D3D11RenderWindow : public RenderWindow
	{
	public:
		D3D11RenderWindow(const RENDER_WINDOW_DESC& desc, UINT32 windowId,
			D3D11Device& device, IDXGIFactory* DXGIFactory);

		~D3D11RenderWindow();

		/** @copydoc RenderWindow::move */
		void move(INT32 left, INT32 top) override;

		/** @copydoc RenderWindow::resize */
		void resize(UINT32 width, UINT32 height) override;

		/** @copydoc RenderWindow::setHidden */
		void setHidden(bool hidden) override;

		/** @copydoc RenderWindow::setActive */
		void setActive(bool state) override;

		/** @copydoc RenderWindow::minimize */
		void minimize() override;

		/** @copydoc RenderWindow::maximize */
		void maximize() override;

		/** @copydoc RenderWindow::restore */
		void restore() override;

		/** @copydoc RenderWindow::setFullscreen(UINT32, UINT32, float, UINT32) */
		void setFullscreen(UINT32 width, UINT32 height, float refreshRate = 60.0f, UINT32 monitorIdx = 0) override;

		/** @copydoc RenderWindow::setFullscreen(const VideoMode&) */
		void setFullscreen(const VideoMode& videoMode) override;

		/** @copydoc RenderWindow::setWindowed */
		void setWindowed(UINT32 width, UINT32 height) override;

		/** @copydoc RenderWindow::setVSync */
		void setVSync(bool enabled, UINT32 interval = 1) override;

		/** 
		 * Copies the contents of a frame buffer into the pre-allocated buffer. 
		 *
		 * @param[out]	dst		Previously allocated buffer to read the contents into. Must be of valid size.
		 * @param[in]	buffer	Frame buffer to read the contents from.
		 */
		void copyToMemory(PixelData &dst, FrameBuffer buffer);

		/** @copydoc RenderWindow::swapBuffers */
		void swapBuffers(UINT32 syncMask = 0xFFFFFFFF) override;

		/** @copydoc RenderWindow::getCustomAttribute */
		void getCustomAttribute(const String& name, void* pData) const override;

		/** @copydoc RenderWindow::_windowMovedOrResized */
		void _windowMovedOrResized() override;

		/**	Returns presentation parameters used for creating the window swap chain. */
		DXGI_SWAP_CHAIN_DESC* _getPresentationParameters() { return &mSwapChainDesc; }

		/**	Returns internal window handle. */
		HWND _getWindowHandle() const;

	protected:
		friend class bs::D3D11RenderWindow;

		/** @copydoc CoreObject::initialize */
		void initialize() override;

		/**	Creates internal resources dependent on window size. */
		void createSizeDependedD3DResources();

		/**	Destroys internal resources dependent on window size. */
		void destroySizeDependedD3DResources();

		/**	Queries the current DXGI device. Make sure to release the returned object when done with it. */
		IDXGIDevice* queryDxgiDevice(); 

		/**	Creates a swap chain for the window. */
		void createSwapChain();

		/**	Resizes all buffers attached to the swap chain to the specified size. */
		void resizeSwapChainBuffers(UINT32 width, UINT32 height);

		/** @copydoc RenderWindow::getProperties */
		const RenderTargetProperties& getPropertiesInternal() const override { return mProperties; }

		/** @copydoc RenderWindow::getSyncedProperties */
		RenderWindowProperties& getSyncedProperties() override { return mSyncedProperties; }

		/** @copydoc RenderWindow::syncProperties */
		void syncProperties() override;

	protected:
		D3D11Device& mDevice;
		IDXGIFactory* mDXGIFactory;
		bool mSizing;
		bool mIsChild;
		bool mShowOnSwap;

		DXGI_SAMPLE_DESC mMultisampleType;
		UINT32 mRefreshRateNumerator;
		UINT32 mRefreshRateDenominator;

		ID3D11Texture2D* mBackBuffer;
		ID3D11RenderTargetView*	mRenderTargetView;
		SPtr<TextureView> mDepthStencilView;
		SPtr<Texture> mDepthStencilBuffer;

		IDXGISwapChain*	mSwapChain;
		DXGI_SWAP_CHAIN_DESC mSwapChainDesc;
		Win32Window* mWindow;

		RenderWindowProperties mProperties;
		RenderWindowProperties mSyncedProperties;
	};
	
	/** @} */
}}