<<<<<<< HEAD
// Copyright (C) 2017 Jérôme Leclercq
=======
// Copyright (C) 2016 Jérôme Leclercq
>>>>>>> Add new Renderer architecture (far from complete)
// This file is part of the "Nazara Engine - Renderer module"
// For conditions of distribution and use, see copyright notice in Config.hpp

#pragma once

#ifndef NAZARA_RENDERER_HPP
#define NAZARA_RENDERER_HPP

<<<<<<< HEAD
#include <Nazara/Prerequisites.hpp>
#include <Nazara/Math/Matrix4.hpp>
#include <Nazara/Math/Rect.hpp>
#include <Nazara/Renderer/Config.hpp>
#include <Nazara/Renderer/Enums.hpp>
#include <Nazara/Utility/Enums.hpp>

namespace Nz
{
	class Color;
	class Context;
	class GpuQuery;
	class IndexBuffer;
	class RenderTarget;
	struct RenderStates;
	class Shader;
	class Texture;
	class TextureSampler;
	class VertexBuffer;
	class VertexDeclaration;

=======
#include <Nazara/Prerequesites.hpp>
#include <Nazara/Core/DynLib.hpp>
#include <Nazara/Renderer/Config.hpp>
#include <Nazara/Renderer/RendererImpl.hpp>

namespace Nz
{
>>>>>>> Add new Renderer architecture (far from complete)
	class NAZARA_RENDERER_API Renderer
	{
		public:
			Renderer() = delete;
			~Renderer() = delete;
			
			static inline RendererImpl* GetRendererImpl();

			static bool Initialize();

<<<<<<< HEAD
			static bool IsComponentTypeSupported(ComponentType type);
			static bool IsEnabled(RendererParameter parameter);
			static bool IsInitialized();

			static void SetBlendFunc(BlendFunc srcBlend, BlendFunc dstBlend);
			static void SetClearColor(const Color& color);
			static void SetClearColor(UInt8 r, UInt8 g, UInt8 b, UInt8 a = 255);
			static void SetClearDepth(double depth);
			static void SetClearStencil(unsigned int value);
			static void SetDepthFunc(RendererComparison compareFunc);
			static void SetFaceCulling(FaceSide faceSide);
			static void SetFaceFilling(FaceFilling fillingMode);
			static void SetIndexBuffer(const IndexBuffer* indexBuffer);
			static void SetLineWidth(float size);
			static void SetMatrix(MatrixType type, const Matrix4f& matrix);
			static void SetPointSize(float size);
			static void SetRenderStates(const RenderStates& states);
			static void SetScissorRect(const Recti& rect);
			static void SetShader(const Shader* shader);
			static void SetStencilCompareFunction(RendererComparison compareFunc, FaceSide faceSide = FaceSide_FrontAndBack);
			static void SetStencilFailOperation(StencilOperation failOperation, FaceSide faceSide = FaceSide_FrontAndBack);
			static void SetStencilMask(UInt32 mask, FaceSide faceSide = FaceSide_FrontAndBack);
			static void SetStencilPassOperation(StencilOperation passOperation, FaceSide faceSide = FaceSide_FrontAndBack);
			static void SetStencilReferenceValue(unsigned int refValue, FaceSide faceSide = FaceSide_FrontAndBack);
			static void SetStencilZFailOperation(StencilOperation zfailOperation, FaceSide faceSide = FaceSide_FrontAndBack);
			static bool SetTarget(const RenderTarget* target);
			static void SetTexture(unsigned int unit, const Texture* texture);
			static void SetTextureSampler(unsigned int textureUnit, const TextureSampler& sampler);
			static void SetVertexBuffer(const VertexBuffer* vertexBuffer);
			static void SetViewport(const Recti& viewport);
=======
			static inline bool IsInitialized();
>>>>>>> Add new Renderer architecture (far from complete)

			static void Uninitialize();

		private:
<<<<<<< HEAD
			static void EnableInstancing(bool instancing);
			static bool EnsureStateUpdate();
			static bool GenerateDebugShader();
			static void OnContextRelease(const Context* context);
			static void OnIndexBufferRelease(const IndexBuffer* indexBuffer);
			static void OnShaderReleased(const Shader* shader);
			static void OnTextureReleased(const Texture* texture);
			static void OnVertexBufferRelease(const VertexBuffer* vertexBuffer);
			static void OnVertexDeclarationRelease(const VertexDeclaration* vertexDeclaration);
			static void UpdateMatrix(MatrixType type);

=======
			static DynLib s_rendererLib;
			static std::unique_ptr<RendererImpl> s_rendererImpl;
>>>>>>> Add new Renderer architecture (far from complete)
			static unsigned int s_moduleReferenceCounter;
	};
}

#include <Nazara/Renderer/Renderer.inl>

#endif // NAZARA_RENDERER_HPP
