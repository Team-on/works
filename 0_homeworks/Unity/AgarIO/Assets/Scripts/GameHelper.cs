﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Networking;

public class GameHelper : NetworkBehaviour {
	public static int foodMax = 100;
	public static int foodCurr = 0;

	public Vector2 mapSize = new Vector2(20, 20);
	public GameObject mapBackground;
	public GameObject foodPrefab;
	
	[Server]
	void Start () {
		for (int i = 0; i < foodMax; i++)
			CreateFood(Color.green);

		mapBackground.se
	}

	[Server]
	void Update () {
		if(foodCurr < foodMax)
			CreateFood(Color.cyan);
	}

	[Server]
	private void CreateFood(Color c) {
		if (!isServer)
			return;
		GameObject point = Instantiate(foodPrefab);
		point.GetComponent<PointHelper>().color = c;
		point.transform.position = new Vector2(Random.Range(-mapSize.x, mapSize.x), Random.Range(-mapSize.y, mapSize.y));
		NetworkServer.Spawn(point);
	}
}
