#include "stdafx.h"
#include "Material.h"
#include "Shader\Shader.h"
#include "Texture\Texture.h"

CGlobalMaterial::CGlobalMaterial()
{
	::ZeroMemory(m_pReflections, sizeof(MATERIAL) * MAX_MATERIALS);

	m_pReflections[0] = { XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f), XMFLOAT4(1.0f, 0.3f, 0.3f, 1000.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) };
	m_pReflections[1] = { XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f), XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f), XMFLOAT4(0.9f, 0.5f, 0.1f, 0.2f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) };
	m_pReflections[2] = { XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f), XMFLOAT4(0.7f, 0.7f, 0.7f, 1.0f), XMFLOAT4(0.9f, 0.5f, 0.1f, 0.2f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) };
	m_pReflections[3] = { XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f), XMFLOAT4(0.0f, 0.5f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 20.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) };
	m_pReflections[4] = { XMFLOAT4(0.0f, 0.5f, 1.0f, 1.0f), XMFLOAT4(0.5f, 0.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 25.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) };
	m_pReflections[5] = { XMFLOAT4(0.0f, 0.5f, 0.5f, 1.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 30.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) };
	m_pReflections[6] = { XMFLOAT4(0.5f, 0.5f, 1.0f, 1.0f), XMFLOAT4(0.5f, 0.5f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 35.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) };
	m_pReflections[7] = { XMFLOAT4(1.0f, 0.5f, 1.0f, 1.0f), XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 40.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) };
}

void CGlobalMaterial::CreateShaderVariables()
{
	CD3DBufMgr::Instance()->AllocUploadBuffer(m_cbMaterialsDesc, sizeof(MATERIAL) * MAX_MATERIALS);
	m_pcbMapped = static_cast<MATERIAL*>(m_cbMaterialsDesc.pMappedPtr);
	m_cbMaterialsDesc.RootParamIdx = ROOT_PARAMETER_MATERIAL;
}

void CGlobalMaterial::UpdateShaderVariables(ID3D12GraphicsCommandList * pd3dCmdLst)
{
	::memcpy(m_pcbMapped, &m_pReflections, sizeof(MATERIAL) * MAX_MATERIALS);
	pd3dCmdLst->SetGraphicsRootConstantBufferView(m_cbMaterialsDesc.RootParamIdx, m_cbMaterialsDesc.view_desc.BufferLocation); //Lights
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CMaterial::CMaterial() 
	: m_pShader{ nullptr }
	, m_pShadowMapShader{ nullptr }
	, m_pTexture{ nullptr }
{
}

CMaterial::~CMaterial()
{
}

void CMaterial::SetTexture(const shared_ptr<CTexture>& pTexture)
{
	m_pTexture = pTexture;
}

void CMaterial::SetShader(const shared_ptr<CShader>& pShader)
{
	m_pShader = pShader;
}

void CMaterial::SetShadowMapShader(const shared_ptr<CShader>& pShader)
{
	m_pShadowMapShader = pShader;
}

void CMaterial::UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCmdLst)
{
	if (m_pTexture) m_pTexture->UpdateShaderVariables(pd3dCmdLst);
}

void CMaterial::ReleaseShaderVariables()
{
}
