#include "BNS_BaseComponentSystem.h"
#include "BNS_PhysicsComponent.h"
#include "BNS_AGameObject.h"
#include "BNS_PhysicsSystem.h"

BNS_PhysicsComponent::BNS_PhysicsComponent(String name, BNS_AGameObject* owner) : BNS_AComponent(name, ComponentType::Physics, owner)
{
	// whenever a new physics component is initialized. Register to physics system
	BNS_BaseComponentSystem::GetInstance()->GetPhysicsSystem()->RegisterComponent(this);
	UpdateRigidBody();
}

BNS_PhysicsComponent::~BNS_PhysicsComponent()
{
	BNS_BaseComponentSystem::GetInstance()->GetPhysicsSystem()->UnRegisterComponent(this);
	BNS_AComponent::~BNS_AComponent();
}

void BNS_PhysicsComponent::DetachOwner()
{
	BNS_BaseComponentSystem::GetInstance()->GetPhysicsSystem()->UnRegisterComponent(this);
	BNS_AComponent::DetachOwner();
}

void BNS_PhysicsComponent::UpdateRigidBody()
{
	PhysicsCommon* physicsCommon = BNS_BaseComponentSystem::GetInstance()->GetPhysicsSystem()->GetPhysicsCommon();
	PhysicsWorld* physicsWorld = BNS_BaseComponentSystem::GetInstance()->GetPhysicsSystem()->GetPhysicsWorld();
	// Create a rigid body in the world
	Vector3D scale = GetOwner()->GetLocalScale();
	Transform transform; transform.setFromOpenGL(GetOwner()->GetPhysicsLocalMatrix());
	this->boxShape = physicsCommon->createBoxShape(Vector3(scale.m_x / 2, scale.m_y / 2, scale.m_z / 2));
	this->rigidBody = physicsWorld->createRigidBody(transform);
	this->rigidBody->addCollider(this->boxShape, transform);
	this->rigidBody->updateMassPropertiesFromColliders();
	this->rigidBody->setMass(this->mass);
	this->rigidBody->setType(BodyType::DYNAMIC);

	transform = this->rigidBody->getTransform();
	float matrix[16];
	transform.getOpenGLMatrix(matrix);

	GetOwner()->RecomputeMatrix(matrix);
}

void BNS_PhysicsComponent::Perform(float deltaTime)
{
	const Transform transform = this->rigidBody->getTransform();
	float matrix[16];
	transform.getOpenGLMatrix(matrix);

	GetOwner()->RecomputeMatrix(matrix);
	//std::cout << "My component is updating: " << this->name << "\n";

	
}

RigidBody* BNS_PhysicsComponent::GetRigidBody()
{
	return this->rigidBody;
}
