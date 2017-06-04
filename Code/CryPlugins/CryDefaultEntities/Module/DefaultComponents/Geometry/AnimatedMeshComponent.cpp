#include "StdAfx.h"
#include "AnimatedMeshComponent.h"

#include <Cry3DEngine/IRenderNode.h>

namespace Cry
{
namespace DefaultComponents
{
static void RegisterAnimatedMeshComponent(Schematyc::IEnvRegistrar& registrar)
{
	Schematyc::CEnvRegistrationScope scope = registrar.Scope(IEntity::GetEntityScopeGUID());
	{
		Schematyc::CEnvRegistrationScope componentScope = scope.Register(SCHEMATYC_MAKE_ENV_COMPONENT(CAnimatedMeshComponent));
		// Functions
		{
			auto pFunction = SCHEMATYC_MAKE_ENV_FUNCTION(&CAnimatedMeshComponent::PlayAnimation, "{DCEBBA52-CECE-4823-AC35-1A590A944F99}"_cry_guid, "PlayAnimation");
			pFunction->SetDescription("Plays a low-level animation on the animated mesh");
			pFunction->SetFlags(Schematyc::EEnvFunctionFlags::None);
			pFunction->BindInput(1, 'name', "Name");
			pFunction->BindInput(2, 'loop', "Looped");
			componentScope.Register(pFunction);
		}
		{
			auto pFunction = SCHEMATYC_MAKE_ENV_FUNCTION(&CAnimatedMeshComponent::SetPlaybackSpeed, "{DDF693D5-100C-43C2-8351-46FD6D382425}"_cry_guid, "SetPlaybackSpeed");
			pFunction->SetDescription("Sets the speed at which animations are played");
			pFunction->SetFlags(Schematyc::EEnvFunctionFlags::Construction);
			pFunction->BindInput(1, 'sped', "Speed");
			componentScope.Register(pFunction);
		}
		{
			auto pFunction = SCHEMATYC_MAKE_ENV_FUNCTION(&CAnimatedMeshComponent::SetPlaybackWeight, "{79D18B21-F255-43C5-98F8-42E131FB2915}"_cry_guid, "SetPlaybackWeight");
			pFunction->SetDescription("Sets the weight at which animations are played");
			pFunction->SetFlags(Schematyc::EEnvFunctionFlags::Construction);
			pFunction->BindInput(1, 'weig', "Weight");
			componentScope.Register(pFunction);
		}
		{
			auto pFunction = SCHEMATYC_MAKE_ENV_FUNCTION(&CAnimatedMeshComponent::SetLayer, "{3CF9CE51-5520-4D6D-8077-8112DA4A48B6}"_cry_guid, "SetLayer");
			pFunction->SetDescription("Sets the layer at which animations are played");
			pFunction->SetFlags(Schematyc::EEnvFunctionFlags::Construction);
			pFunction->BindInput(1, 'layr', "Layer");
			componentScope.Register(pFunction);
		}
	}
}

void CAnimatedMeshComponent::ReflectType(Schematyc::CTypeDesc<CAnimatedMeshComponent>& desc)
{
	desc.SetGUID(CAnimatedMeshComponent::IID());
	desc.SetEditorCategory("Geometry");
	desc.SetLabel("Animated Mesh");
	desc.SetDescription("A component containing a simple mesh that can be animated");
	desc.SetComponentFlags({ IEntityComponent::EFlags::Transform, IEntityComponent::EFlags::Socket, IEntityComponent::EFlags::Attach });

	desc.AddMember(&CAnimatedMeshComponent::m_filePath, 'file', "FilePath", "File", "Determines the animated mesh to load", "");
	desc.AddMember(&CAnimatedMeshComponent::m_defaultAnimation, 'anim', "Animation", "Default Animation", "Specifies the animation we want to play by default", "");
	desc.AddMember(&CAnimatedMeshComponent::m_bLoopDefaultAnimation, 'loop', "Loop", "Loop Default", "Whether or not to loop the default animation", false);
}

void CAnimatedMeshComponent::Run(Schematyc::ESimulationMode simulationMode)
{
	Initialize();
}

void CAnimatedMeshComponent::SetCharacterFile(const char* szPath)
{
	m_filePath = szPath;
}

void CAnimatedMeshComponent::SetDefaultAnimationName(const char* szPath)
{
	m_defaultAnimation = szPath;
}
}
}
