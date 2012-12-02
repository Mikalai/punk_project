#include <ostream>
#include <math.h>
#include <istream>
#include "../../math/helper.h"
#include "armature_animation_mixer.h"
#include "bone_animation.h"
#include "../skinning/armature.h"
#include "../../system/logger.h"

namespace Virtual
{
	ArmatureAnimationMixer::ArmatureAnimationMixer() 
		: m_current_time(0)
	{}

	ArmatureAnimationMixer::~ArmatureAnimationMixer()
	{
	}

	bool ArmatureAnimationMixer::GetBoneMatrix(const System::string& bone, Math::mat4& matrix)
	{
		try
		{
			Math::mat4 pos = Math::mat4::CreateTranslate(m_result.at(bone).m_position);
			Math::mat4 rot = Math::QuaternionToMatrix4x4(m_result.at(bone).m_rotation);
			matrix = pos*rot;
			return true;
		}
		catch(std::out_of_range&)
		{
			out_error() << "No bone in armature with name " << bone << std::endl;
			return false;
		}
		return true;
	}

	void ArmatureAnimationMixer::SetTrackTime(float frame)
	{
		for (auto bone : m_result)
		{
			bone.second.m_position.Set(0,0,0);
			bone.second.m_rotation.Set(0,0,0,0);
		}

		for (auto named_track : m_tracks)
		{
			const System::string& name = named_track.first;
			try
			{
				TrackOption& options = m_options.at(name);
				
				float time = frame;
				//	find correct time
				if (options.m_enable)
				{
					if (time > options.m_max_time)
						if (options.m_loop)
							if (options.m_max_time > 0)
								while (time > options.m_max_time) time -= options.m_max_time;
							else
							{
								out_error() << "Bad Max time of the frame " << name << " with value " << options.m_max_time << std::endl;
								return;
							}
						else
							time = options.m_max_time;

					//	animation for all bones
					auto armature_anim = named_track.second;
					for (auto anim : armature_anim)
					{
						const System::string& bone_name = anim.first;
						const BoneAnimation* track = anim.second;

						Math::vec3 pos = track->GetPosition(time);
						Math::quat rot = track->GetRotation(time);

						m_result[bone_name].m_position += pos * options.m_weight;
						m_result[bone_name].m_rotation += rot * options.m_weight;
					}					
				}
			}
			catch(std::out_of_range&)
			{
				out_error() << L"No options for track " << name << std::endl;
				return;
			}
		}
	}

	void ArmatureAnimationMixer::EnableTrack(const System::string& track_name, bool flag)
	{
		m_options[track_name].m_enable = flag;
	}

	void ArmatureAnimationMixer::DisableAllTracks()
	{
		for (auto option : m_options)
		{
			option.second.m_enable = false;
		}
	}

	void ArmatureAnimationMixer::SetTrackWeight(const System::string& track_name, float value)
	{
		m_options[track_name].m_weight = value;
	}

	void ArmatureAnimationMixer::SetLooping(const System::string& track_name, bool flag)
	{
		m_options[track_name].m_loop = flag;
	}

	bool ArmatureAnimationMixer::Save(std::ostream& stream) const
	{
		return false;
	}

	bool ArmatureAnimationMixer::Load(std::istream& stream)
	{
		return false;
	}
}