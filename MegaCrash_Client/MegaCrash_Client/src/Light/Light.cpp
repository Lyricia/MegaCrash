// main.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Light.h"

CLight::CLight()
{
	::ZeroMemory(this, sizeof(CLight));

	m_Lights.xmf4GlobalAmbient = XMFLOAT4(0.375f, 0.375f, 0.375f, 1.0f);

	m_Lights.params[0].bEnable = true;
	m_Lights.params[0].nType = DIRECTIONAL_LIGHT;
	m_Lights.params[0].xmf3Position = XMFLOAT3(0.0f, 4100.f, 0.0f);
	m_Lights.params[0].xmf4Ambient = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	m_Lights.params[0].xmf4Diffuse = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	m_Lights.params[0].xmf4Specular = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	m_Lights.params[0].xmf3Direction = XMFLOAT3(1.0f, -1.0f, 1.0f);

	//m_Lights.params[1].bEnable = true;
	//m_Lights.params[1].nType = SPOT_LIGHT;
	//m_Lights.params[1].fRange = 600.0f;
	//m_Lights.params[1].xmf4Ambient = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);
	//m_Lights.params[1].xmf4Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	//m_Lights.params[1].xmf4Specular = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	//m_Lights.params[1].xmf3Position = XMFLOAT3(-50.0f, 20.0f, -5.0f);
	//m_Lights.params[1].xmf3Direction = XMFLOAT3(0.0f, 0.0f, 1.0f);
	//m_Lights.params[1].xmf3Attenuation = XMFLOAT3(1.0f, 0.001f, 0.00001f);
	//m_Lights.params[1].fFalloff = 2.0f;
	//m_Lights.params[1].fPhi = (float)cos(XMConvertToRadians(40.0f));
	//m_Lights.params[1].fTheta = (float)cos(XMConvertToRadians(25.0f));

	//m_Lights.params[0].bEnable = false;
	//m_Lights.params[0].nType = POINT_LIGHT;
	//m_Lights.params[0].fRange = 100.0f;
	//m_Lights.params[0].xmf4Ambient = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);
	//m_Lights.params[0].xmf4Diffuse = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	//m_Lights.params[0].xmf4Specular = XMFLOAT4(0.1f, 0.1f, 0.1f, 0.0f);
	//m_Lights.params[0].xmf3Position = XMFLOAT3(130.0f, 30.0f, 30.0f);
	//m_Lights.params[0].xmf3Direction = XMFLOAT3(0.0f, 0.0f, 0.0f);
	//m_Lights.params[0].xmf3Attenuation = XMFLOAT3(1.0f, 0.001f, 0.0001f);
}

void CLight::CreateShaderVariables()
{
	CD3DBufMgr::Instance()->AllocUploadBuffer(m_cbLightsDesc, sizeof(LIGHTS));
	m_pcbMapped = static_cast<LIGHTS*>(m_cbLightsDesc.pMappedPtr);
	m_cbLightsDesc.RootParamIdx = ROOT_PARAMETER_LIGHT;
}

void CLight::UpdateShaderVariables(ID3D12GraphicsCommandList * pd3dCmdLst)
{
	::memcpy(m_pcbMapped, &m_Lights, sizeof(LIGHTS));
	pd3dCmdLst->SetGraphicsRootConstantBufferView(m_cbLightsDesc.RootParamIdx, m_cbLightsDesc.view_desc.BufferLocation); //Lights
}