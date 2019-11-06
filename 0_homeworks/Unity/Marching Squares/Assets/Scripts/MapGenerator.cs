using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using Random = UnityEngine.Random;

[RequireComponent(typeof(MeshGenerator))]
public class MapGenerator : MonoBehaviour {
	public int width = 128;
	public int height = 72;

	public int wallThresholdSize = 25;
	public int roomThresholdSize = 25;
	public int borderSize = 5;

	public float squareSize = 1;
	public float smoothLevel = 5;

	public string seed;
	public bool useRandomSeed = true;

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

		for (int i = 0; i < smoothLevel; i++) 
			SmoothMap();

		RemoveSmallRooms();
		ConnectRooms();

		int[,] borderedMap = GetBorderedMap();

		MeshGenerator meshGen = GetComponent<MeshGenerator>();
		meshGen.GenerateMesh(borderedMap, squareSize);
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
		foreach (List<Coord> wallRegion in wallRegions) {
			if (wallRegion.Count < wallThresholdSize) {
				foreach (Coord tile in wallRegion) {
					map[tile.x, tile.y] = 0;
				}
			}
		}

		List<List<Coord>> roomRegions = GetRegions(0);
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

	void ConnectRooms() {
		List<List<Coord>> roomRegions = GetRegions(0);

		List<Room> rooms = new List<Room>();

		foreach (List<Coord> roomRegion in roomRegions) 
			rooms.Add(new Room(roomRegion, map));

		RoomConnection[,] prices = new RoomConnection[rooms.Count, rooms.Count];

		int bestDistance = int.MaxValue;
		Coord bestA = new Coord(), bestB = new Coord();

		for (int i = 0; i < rooms.Count - 1; ++i) {
			Room roomA = rooms[i];
			prices[i, i] = new RoomConnection() {
				dist = int.MaxValue,
			};

			for (int j = i + 1; j < rooms.Count; ++j) {
				Room roomB = rooms[j];
				bestDistance = int.MaxValue;

				for (int tileIndexA = 0; tileIndexA < roomA.edgeTiles.Count; tileIndexA++) {
					for (int tileIndexB = 0; tileIndexB < roomB.edgeTiles.Count; tileIndexB++) {
						Coord tileA = roomA.edgeTiles[tileIndexA];
						Coord tileB = roomB.edgeTiles[tileIndexB];
						int distanceBetweenRooms = (int)(Mathf.Pow(tileA.x - tileB.x, 2) + Mathf.Pow(tileA.y - tileB.y, 2));

						if (distanceBetweenRooms < bestDistance) {
							bestDistance = distanceBetweenRooms;
							bestA = tileA;
							bestB = tileB;
						}
					}
				}

				prices[i, j].dist = bestDistance;
				prices[i, j].tileA = bestA;
				prices[i, j].tileB = bestB;

				prices[j, i].dist = bestDistance;
				prices[j, i].tileA = bestA;
				prices[j, i].tileB = bestB;
			}
		}
		prices[rooms.Count - 1, rooms.Count - 1] = new RoomConnection() {
			dist = int.MaxValue,
		};


		for (int i = 0; i < rooms.Count - 1; ++i) {
			int minId = i + 1;
			for (int j = i + 2; j < rooms.Count; ++j) {
				if (prices[i, minId].dist > prices[i, j].dist)
					minId = j;
			}
			CreatePassage(rooms[i], rooms[minId], prices[i, minId].tileA, prices[i, minId].tileB);
			Debug.Log($"{i} -> {minId}");
		}
	}

	void CreatePassage(Room roomA, Room roomB, Coord tileA, Coord tileB) {
		Room.ConnectRooms(roomA, roomB);
		Debug.DrawLine(CoordToWorldPoint(tileA), CoordToWorldPoint(tileB), Color.green, 100);
	}

	Vector3 CoordToWorldPoint(Coord tile) {
		return new Vector3(-width / 2 + .5f + tile.x, 2, -height / 2 + .5f + tile.y);
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

	class Room {
		public List<Coord> tiles;
		public List<Coord> edgeTiles;
		public List<Room> connectedRooms;
		public int roomSize;

		public Room() { }

		public Room(List<Coord> roomTiles, int[,] map) {
			tiles = roomTiles;
			roomSize = tiles.Count;
			connectedRooms = new List<Room>();

			edgeTiles = new List<Coord>();
			foreach (Coord tile in tiles) 
				for (int x = tile.x - 1; x <= tile.x + 1; x++) 
					for (int y = tile.y - 1; y <= tile.y + 1; y++) 
						if (x == tile.x || y == tile.x && map[x, y] == 1) 
								edgeTiles.Add(tile);
		}

		public static void ConnectRooms(Room roomA, Room roomB) {
			roomA.connectedRooms.Add(roomB);
			roomB.connectedRooms.Add(roomA);
		}

		public bool IsConnected(Room otherRoom) {
			return connectedRooms.Contains(otherRoom);
		}
	}

	struct RoomConnection {
		public Coord tileA;
		public Coord tileB;
		public int dist;
	}
}