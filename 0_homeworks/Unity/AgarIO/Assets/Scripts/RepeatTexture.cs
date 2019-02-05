using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RepeatTexture : MonoBehaviour {
	void Start () {
		var t = GetComponent<MeshRenderer>().material.mainTexture;
		t.wrapMode = TextureWrapMode.Repeat;
	}
}
