#include "..\SceneList.h"
#include "..\..\..\Common\Mesh\Dx9SkinMesh\Dx9SkinMesh.h"
#include "..\..\..\Common\Mesh\Dx9StaticMesh\Dx9StaticMesh.h"
#include "..\..\..\Resource\MeshResource\MeshResource.h"
#include "..\..\..\Utility\Input\Input.h"
#include "..\..\..\Object\Fade\Fade.h"
#include "..\..\..\Object\Collider\Sphere\Sphere.h"
#include "..\..\..\Object\Collider\Capsule\Capsule.h"
#include "..\..\..\Object\Collider\CollisionRender\CollisionRender.h"
#include "..\..\..\Object\CameraBase\CameraManager\CameraManager.h"
#include "..\..\..\Object\Collider\CollisionManager\CollisionManager.h"
#include "..\..\..\Object\Collider\Box\Box.h"
#include "..\..\..\Object\Collider\Ray\Ray.h"
#include "..\..\..\Utility\XAudio2\SoundManager.h"
#include "..\..\..\Resource\SpriteResource\SpriteResource.h"

CTitle::CTitle( CSceneManager* pSceneManager )
	: CSceneBase	( pSceneManager )
	, m_pSkinMesh	( nullptr )
	, m_pStaticMesh	( nullptr )
{
}

CTitle::~CTitle()
{
}

//============================.
//	�Ǎ��֐�.
//============================.
bool CTitle::Load()
{
	m_pSkinMesh = CMeshResorce::GetSkin("kaito_s");
	m_pStaticMesh = CMeshResorce::GetStatic("stage");
	m_Sprite = CSpriteResource::GetSprite("pokemon");
	return true;
}

//============================.
//	�X�V�֐�.
//============================.
void CTitle::Update()
{
	m_DeltaTime = GetDeltaTime();
	m_pSkinMesh->SetAnimSpeed( GetDeltaTime<double>() );

	static D3DXVECTOR3 pos = { 0.0f, 0.0f, 0.0f };
	static D3DXVECTOR3 pos2 = { 0.0f, 0.0f, 1.0f };
	static float rot = 0.0f, rot_y = 0.0f;

	if( CKeyInput::IsPress('I') == true ) pos.x += 0.01f;
	if( CKeyInput::IsPress('K') == true ) pos.x -= 0.01f;
	if( CKeyInput::IsPress('J') == true ) pos.y += 0.01f;
	if( CKeyInput::IsPress('L') == true ) pos.y -= 0.01f;
	if( CKeyInput::IsPress('U') == true ) pos.z += 0.01f;
	if( CKeyInput::IsPress('O') == true ) pos.z -= 0.01f;

	if( CKeyInput::IsPress('I') == true ) pos2.x += 0.01f;
	if( CKeyInput::IsPress('K') == true ) pos2.x -= 0.01f;
	if( CKeyInput::IsPress('J') == true ) pos2.y += 0.01f;
	if( CKeyInput::IsPress('L') == true ) pos2.y -= 0.01f;
	if( CKeyInput::IsPress('U') == true ) pos2.z += 0.01f;
	if( CKeyInput::IsPress('O') == true ){
		pos2.z -= 0.01f;
	}
	
	if( CKeyInput::IsPress('H') == true ){
		rot += 0.01f;
	}
	if( CKeyInput::IsPress('M') == true ){
		rot_y += 0.01f;
	}

	//�ǉ��R�����g
	static CSphere sphere, s1, s2;
	static CRay ray;
	D3DXVECTOR3 vec;
	D3DXVec3Normalize( &vec, &D3DXVECTOR3( cosf(rot), sinf(rot_y), sinf(rot) ) );
	ray.SetVector( vec );
	ray.SetStartPos( pos );
	ray.SetEndPos( pos2 );
	sphere.SetPosition( { 0.0f, 1.0f, 0.0f } );

	D3DXVECTOR3 p, p2;
	s1.SetRadius( 0.1f );
	s2.SetRadius( 0.1f );

	bool isHit = coll::IsRayToSphere( &ray, &sphere, &p, &p2 );
	s1.SetPosition( p );
	s2.SetPosition( p2 );

	if( CKeyInput::IsMomentPress('G') == true ){
		SetSceneChange();
	}
}

//============================.
// ���f���`��֐�.
//============================.
void CTitle::ModelRender()
{
	m_pStaticMesh->Render();
	m_pSkinMesh->Render();

	SSpriteRenderState s = m_Sprite->GetRenderState();
	s.Tranceform.Scale = { 3.0f, 3.0f, 3.0f };
	m_Sprite->Render3D( false, &s );

}

//============================.
// �摜�`��֐�.
//============================.
void CTitle::SpriteRender()
{
}

