using UnityEngine;
using UnityEngine.Networking;
using System.Collections;

public class NavMeshAgentMover : NetworkBehaviour {
	[Header("NetworkSettings")]
	public float SyncRate = 3;

	[SyncVar]
	Vector3 position;
	[SyncVar]
	Quaternion rotation;

	Animator animator;
	NavMeshAgent navMeshAgent;
	Vector3 target;

	void Start() {
		navMeshAgent = GetComponent<NavMeshAgent>();
		animator = GetComponent<Animator>();
		target = transform.position;
	}

	[ServerCallback]
	void Update() {
		Animation();

		if (position == transform.position && rotation == transform.rotation)
			return;

		position = transform.position;
		rotation = transform.rotation;
	}

	[ClientCallback]
	void FixedUpdate() {
		if (transform.position != position)
			transform.position = Vector3.Lerp(transform.position, position, Time.deltaTime * SyncRate);
		if (transform.rotation != rotation)
			transform.rotation = Quaternion.Lerp(transform.rotation, rotation, Time.deltaTime * SyncRate);
	}

	public void Move(Vector3 point) {
		CmdMove(point);
	}

	[Command]
	void CmdMove(Vector3 point) {
		target = point;
		navMeshAgent.SetDestination(target);
	}

	void Animation() {
		bool isRunning = Vector3.Distance(transform.position, target) > navMeshAgent.stoppingDistance;
		bool isNearStop = Vector3.Distance(transform.position, target) <= navMeshAgent.stoppingDistance;

		animator.SetBool("IsRunning", isRunning);
		animator.SetBool("IsNearStop", isNearStop);
	}
}
