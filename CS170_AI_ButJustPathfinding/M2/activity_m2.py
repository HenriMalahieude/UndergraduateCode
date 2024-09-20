from typing import List, Tuple

def dir_is_edge(grid, coord):
	x, y = coord
	if (0 <= x < len(grid)) and (0 <= y < len(grid[0])):
		return grid[coord[0]][coord[1]] == "0"
	else:
		return True

class ActivityM2:
	def find_edges(grid: List[List[str]]):
		isles = []
		visited = []
		m, n = len(grid), len(grid[0])

		def BFS(x, y):
			perimeter = []
			q = [(x, y)]
			while len(q) > 0:
				cx, cy = q.pop(0)
				cur_coord = (cx, cy)
				if (0 <= cx < m) and (0 <= cy < n):
					if cur_coord not in visited and grid[cx][cy] == "1":
						visited.append(cur_coord)
						
						#North
						north = (cx, cy + 1)
						q.append(north)

						#East
						east = (cx + 1, cy)
						q.append(east)

						#South
						south = (cx, cy - 1)
						q.append(south)

						#West
						west = (cx - 1, cy)
						q.append(west)

						if dir_is_edge(grid, north) or dir_is_edge(grid, east) or dir_is_edge(grid, south) or dir_is_edge(grid, west):
							if cur_coord not in perimeter:
								perimeter.append(cur_coord)

			return perimeter
		
		for i in range(m):
			for j in range(n):
				if grid[i][j] == "1" and (i,j) not in visited:
					island = BFS(i, j)
					fmt_island = set()
					for (x, y) in island:
						fmt_island.add(x*n + y)
					#fmt_island.sort()
					isles.append(fmt_island)

		return isles

if __name__ == "__main__":
	example1 = {
		"problem": [
			["1","1","1","1","1"], 
			["1","1","0","1","0"],
			["1","1","0","0","0"], 
			["0","0","0","0","0"] 
		],

		"answer": [
			[0, 1, 2, 3, 4, 5, 6, 8, 10, 11]
		]
	}

	example2 = {
		"problem": [
			["1","1","0","0","0"], 
			["1","1","0","0","0"], 
			["0","0","1","0","0"],
			["0","0","0","1","1"] 
		],

		"answer": [
			[0,1,5,6],
			[12],
			[18,19]
		]
	}

	print(ActivityM2.find_edges(example2["problem"]))