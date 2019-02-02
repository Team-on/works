using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MoveRight : MonoBehaviour {

	void Start () {
		
	}
	
	void Update () {
		GetComponent<Rigidbody>().AddForce(Vector3.right);
	}
}
