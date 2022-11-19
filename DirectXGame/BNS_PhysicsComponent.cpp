#include "BNS_BaseComponentSystem.h"
#include "BNS_PhysicsComponent.h"
#include "BNS_AGameObject.h"
#include "BNS_PhysicsSystem.h"

BNS_PhysicsComponent::BNS_PhysicsComponent(String name, AGameObjectPtr owner) : BNS_AComponent(name, ComponentType::Physics, owner)
{
	// whenever a new physics component is initialized. Register to physics system
	BNS_BaseComponentSystem::GetInstance()->GetPhysicsSystem()->RegisterComponent(this);
	PhysicsCommon* physicsCommon = BNS_BaseComponentSystem::GetInstance()->GetPhysicsSystem()->GetPhysicsCommon();
	PhysicsWorld* physicsWorld = BNS_BaseComponentSystem::GetInstance()->GetPhysicsSystem()->GetPhysicsWorld();

	// Create a rigid body in the world
	Vector3D scale = GetOwner()->GetLocalScale();
	Transform transform; transform.setFromOpenGL(GetOwner()->GetPhysicsLocalMatrix());
	BoxShape* boxShape = physicsCommon->createBoxShape(Vector3(scale.m_x / 2, scale.m_y / 2, scale.m_z / 2));
	rigidBody = physicsWorld->createRigidBody(transform);
	rigidBody->addCollider(boxShape, transform);
	rigidBody->updateMassPropertiesFromColliders();
	rigidBody->setMass(mass);
	rigidBody->setType(BodyType::DYNAMIC);

	transform = rigidBody->getTransform();
	float matrix[16];
	transform.getOpenGLMatrix(matrix);

	GetOwner().get()->RecomputeMatrix(matrix);
}

BNS_PhysicsComponent::~BNS_PhysicsComponent()
{
	BNS_AComponent::~BNS_AComponent();
	BNS_BaseComponentSystem::GetInstance()->GetPhysicsSystem()->UnRegisterComponent(this);
}

void BNS_PhysicsComponent::Perform(float deltaTime)
{
	const Transform transform = rigidBody->getTransform();
	float matrix[16];
	transform.getOpenGLMatrix(matrix);

	GetOwner().get()->RecomputeMatrix(matrix);
	//std::cout << "My component is updating: " << this->name << "\n";
}

RigidBody* BNS_PhysicsComponent::GetRigidBody()
{
	return rigidBody;
}
