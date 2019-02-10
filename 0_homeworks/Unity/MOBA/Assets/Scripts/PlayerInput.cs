using UnityEngine;
using UnityEngine.Networking;
using System.Collections;

[RequireComponent(typeof(NavMeshAgentMover))]
public class PlayerInput : NetworkBehaviour {
	NavMeshAgentMover navMeshAgentMover;

	void Start(){
		if (!isLocalPlayer){ 
			enabled = false;
			return;
		}

		navMeshAgentMover = GetComponent<NavMeshAgentMover>();
	}

	void Update() {
		if(Input.GetMouseButtonDown(0)){
			RaycastHit hit;
			Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
			if(Physics.Raycast(ray, out hit) && hit.transform.tag == "Ground")
				navMeshAgentMover.Move(hit.point);
		}
	}
}
