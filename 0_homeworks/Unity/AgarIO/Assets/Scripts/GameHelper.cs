using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Networking;

public class GameHelper : NetworkBehaviour {
	public GameObject foodPrefab;

	[Server]
	void Start () {
		for (int i = 0; i < 10; i++) {
			GameObject point = Instantiate(foodPrefab);
			point.transform.position = Random.insideUnitCircle * Random.Range(10, 30);
			NetworkServer.Spawn(point);
		}
	}
	
	void Update () {
		
	}
}
