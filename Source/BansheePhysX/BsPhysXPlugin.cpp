#include "BsPhysXPrerequisites.h"
#include "Physics/BsPhysicsManager.h"
#include "BsPhysX.h"

namespace bs
{
	class BS_PLUGIN_EXPORT PhysXFactory : public PhysicsFactory
	{
	public:
		void startUp(bool cooking) override
		{
			PHYSICS_INIT_DESC desc;
			desc.initCooking = cooking;

			Physics::startUp<PhysX>(desc);
		}

		void shutDown() override
		{
			Physics::shutDown();
		}
	};

	extern "C" BS_PLUGIN_EXPORT PhysXFactory* loadPlugin()
	{
		return bs_new<PhysXFactory>();
	}

	extern "C" BS_PLUGIN_EXPORT void unloadPlugin(PhysXFactory* instance)
	{
		bs_delete(instance);
	}
}