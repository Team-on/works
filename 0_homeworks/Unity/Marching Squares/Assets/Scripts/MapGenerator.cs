using System;
using System.Collections;
using System.Collections.Generic;
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
		if (Input.GetMouseButtonDown(0)) {
			GenerateMap();
		}
		else if (Input.GetMouseButtonDown(1)) {
			map = new int[width, height];
				RandomFillMap();

				for (int i = 0; i < 5; i++)
					SmoothMap();


				int[,] borderedMap = GetBorderedMap();

				MeshGenerator meshGen = GetComponent<MeshGenerator>();
				meshGen.GenerateMesh(borderedMap, 1);
		}
	}

	void GenerateMap() {
		map = new int[width, height];
		RandomFillMap();

		for (int i = 0; i < 5; i++) 
			SmoothMap();

		RemoveSmallRooms();

		int[,] borderedMap = GetBorderedMap();

		MeshGenerator meshGen = GetComponent<MeshGenerator>();
		meshGen.GenerateMesh(borderedMap, 1);
	}

	void RandomFillMap() {
		if (useRandomSeed) 
			Random.InitState((int)Time.time);
		else
			Random.InitState(seed.GetHashCode());

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
				if (IsInMapRange(neighbourX, neighbourY)) {
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

	void RemoveSmallRooms() {
		List<List<Coord>> wallRegions = GetRegions(1);
		int wallThresholdSize = 50;

		foreach (List<Coord> wallRegion in wallRegions) {
			if (wallRegion.Count < wallThresholdSize) {
				foreach (Coord tile in wallRegion) {
					map[tile.x, tile.y] = 0;
				}
			}
		}

		List<List<Coord>> roomRegions = GetRegions(0);
		int roomThresholdSize = 50;

		foreach (List<Coord> roomRegion in roomRegions) {
			if (roomRegion.Count < roomThresholdSize) {
				foreach (Coord tile in roomRegion) {
					map[tile.x, tile.y] = 1;
				}
			}
		}
	}

	List<List<Coord>> GetRegions(int tileType) {
		List<List<Coord>> regions = new List<List<Coord>>();
		int[,] mapFlags = new int[width, height];

		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				if (mapFlags[x, y] == 0 && map[x, y] == tileType) {
					List<Coord> newRegion = new List<Coord>();

					Queue<Coord> queue = new Queue<Coord>();
					queue.Enqueue(new Coord(x, y));

					while (queue.Count > 0) {
						Coord tile = queue.Dequeue();
						mapFlags[tile.x, tile.y] = 1;
						newRegion.Add(tile);

						FillTile(tile.x - 1, tile.y, queue);
						FillTile(tile.x + 1, tile.y, queue);
						FillTile(tile.x, tile.y - 1, queue);
						FillTile(tile.x, tile.y + 1, queue);
					}

					regions.Add(newRegion);
				}
			}
		}

		return regions;

		void FillTile(int x, int y, Queue<Coord> queue) {
			if (IsInMapRange(x, y) && mapFlags[x, y] == 0 && map[x, y] == tileType) {
				mapFlags[x, y] = 1;
				queue.Enqueue(new Coord(x, y));
			}
		}
	}

	int[,] GetBorderedMap() {
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

		return borderedMap;
	}

	bool IsInMapRange(int x, int y) {
		return x >= 0 && x < width && y >= 0 && y < height;
	}

	struct Coord {
		public int x;
		public int y;

		public Coord(int _x, int _y) {
			x = _x;
			y = _y;
		}
	}
}