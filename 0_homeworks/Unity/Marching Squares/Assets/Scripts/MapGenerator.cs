﻿using System;
using System.Collections;
using UnityEngine;

using Random = UnityEngine.Random;

[RequireComponent(typeof(MeshGenerator))]
public class MapGenerator : MonoBehaviour {
	public int width;
	public int height;

	public string seed;
	public bool useRandomSeed;

	[Range(0, 100)]
	public int randomFillPercent;

	int[,] map;

	void Start() {
		GenerateMap();
	}

	void Update() {
		if (Input.GetMouseButtonDown(0))
			GenerateMap();
	}

	void GenerateMap() {
		map = new int[width, height];
		RandomFillMap();

		for (int i = 0; i < 5; i++) 
			SmoothMap();

		int borderSize = 5;
		int[,] borderedMap = new int[width + borderSize * 2, height + borderSize * 2];

		for (int x = 0; x < borderedMap.GetLength(0); x++) {
			for (int y = 0; y < borderedMap.GetLength(1); y++) {
				if (
					borderSize <= x && x < width + borderSize &&
					borderSize <= y && y < height + borderSize
				) {
					borderedMap[x, y] = map[x - borderSize, y - borderSize];
				}
				else
					borderedMap[x, y] = 1;
			}
		}

		MeshGenerator meshGen = GetComponent<MeshGenerator>();
		meshGen.GenerateMesh(borderedMap, 1);
	}

	void RandomFillMap() {
		if (useRandomSeed) 
			Random.InitState((int)Time.time);

		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				if (x == 0 || x == width - 1 || y == 0 || y == height - 1) {
					map[x, y] = 1;
				}
				else {
					map[x, y] = (Random.Range(0, 100) < randomFillPercent) ? 1 : 0;
				}
			}
		}
	}

	void SmoothMap() {
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				int neighbourWallTiles = GetSurroundingWallCount(x, y);

				if (neighbourWallTiles > 4)
					map[x, y] = 1;
				else if (neighbourWallTiles < 4)
					map[x, y] = 0;

			}
		}
	}

	int GetSurroundingWallCount(int gridX, int gridY) {
		int wallCount = 0;
		for (int neighbourX = gridX - 1; neighbourX <= gridX + 1; neighbourX++) {
			for (int neighbourY = gridY - 1; neighbourY <= gridY + 1; neighbourY++) {
				if (neighbourX >= 0 && neighbourX < width && neighbourY >= 0 && neighbourY < height) {
					if (neighbourX != gridX || neighbourY != gridY) {
						wallCount += map[neighbourX, neighbourY];
					}
				}
				else {
					wallCount++;
				}
			}
		}

		return wallCount;
	}
}