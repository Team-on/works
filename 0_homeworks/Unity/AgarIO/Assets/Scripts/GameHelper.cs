using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Networking;

public class GameHelper : NetworkBehaviour {
	[Server]
	void Start () {
		for (int i = 0; i < 10; i++) {
			print("spawn point");
			//GetComponent<NetworkManager>().spawnPrefabs[0]
			GameObject point = Instantiate(Resources.Load<GameObject>("Point"));
			point.transform.position = Random.insideUnitCircle * Random.Range(10, 30);
			NetworkServer.Spawn(point);
		}
	}
	
	void Update () {
		
	}
}
