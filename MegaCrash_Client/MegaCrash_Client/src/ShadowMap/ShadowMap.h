#pragma once
#include "Light/Light.h"

constexpr UINT SHADOW_MAP_WIDTH{ 8192 };
constexpr UINT SHADOW_MAP_HEIGHT{ 8192 };

class CLight;
class CShadowMap
{
public:
	struct CB_INFO
	{
		XMMATRIX						m_matVPT;
	};

public:
	CShadowMap(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList*	pd3dCmdLst);
	~CShadowMap();

	void CreateShaderVariables(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCmdLst);
	void UpdateShaderVariables(ID3D12GraphicsCommandList* pd3dCmdLst);

	void Render(ID3D12GraphicsCommandList* pd3dCmdLst, CCamera* pCamera = NULL);
	void RenderShadowMap(ID3D12GraphicsCommandList* pd3dCmdLst);

	void SetLight(CLight::LIGHT_PARAMETER* pLight);
	ID3D12Resource* GetDSBuf() { return m_DepthStencilBuf.pResource.Get(); }
	D3D12_CPU_DESCRIPTOR_HANDLE GetDsv() { return m_DepthStencilBuf.hCPUDescTable; }
	CCamera* GetLightCamera() { return m_pLightCamera; }

private:
	DS_DESC							m_DepthStencilBuf;
	shared_ptr<DescriptorHeap>		m_pDSVDescHeap;

	CCamera*						m_pLightCamera;
	CLight::LIGHT_PARAMETER*		m_pLight;

	XMFLOAT4X4						m_matTexture;

	CB_INFO							m_cbInfo;
	CB_INFO*						m_pcbMapped;
	CB_DESC							m_cbDesc;
};