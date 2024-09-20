from typing import List, Tuple

def print_grid(grid: List[List[int]]):
	for row in grid:
		print(*row)

def cardinal_dirs(grid: List[List[int]], coord: Tuple[int, int]) -> List[Tuple[int, int]]:
	r, c = coord
	dirs = []

	if (r - 1) >= 0: #up
		dirs.append((r-1, c))

	if (r + 1) < len(grid): #down
		dirs.append((r+1, c))
	
	if (c - 1) >= 0: #left
		dirs.append((r, c-1))

	if (c + 1) < len(grid[0]): #right
		dirs.append((r, c+1))

	return dirs

def can_speak(grid: List[List[int]], coord: Tuple[int, int]) -> bool:
	if grid[coord[0]][coord[1]] == 1: return
	surround = cardinal_dirs(grid, coord)

	for pos in surround:
		if grid[pos[0]][pos[1]] == 1:
			return False

	return True

class ActivityM3:
	@staticmethod
	def find_whisperers(grid: List[List[int]]) -> Tuple[int, List[List[int]]]:
		m, n = len(grid), len(grid[0])
		representative = [[0 for _ in range(n)] for _ in range(m)]
		outn = 0

		used = set()
		while len(used) < (m * n):
			best_urg = 0
			best_urgt = -300000
			best_coord = (-1, -1)
			best_drop = []
			for i in range(m):
				for j in range(n):
					if can_speak(representative, (i, j)):
						total_urg = grid[i][j]
						surround = cardinal_dirs(grid, (i, j))

						for pos in surround:
							total_urg -= grid[pos[0]][pos[1]]
						
						if total_urg > best_urgt or (total_urg == best_urgt and best_urg < grid[i][j]):
							best_urgt = total_urg
							best_urg = grid[i][j]
							best_coord = (i, j)
							best_drop = surround
			
			representative[best_coord[0]][best_coord[1]] = 1
			used.update(best_drop); used.add(best_coord)
			outn += best_urg

			print("Total Used:", len(used))
			print("Current Urgency Score:", outn)
			print_grid(representative)
			input("\n")

		return outn, representative

if __name__ == "__main__":
	example1 = [
		[1, 3],
		[2, 2]
	] #Solution = 5, [[0, 1], [1, 0]]

	example2 = [
		[1, 2, 4],
		[1, 2, 1],
	] #Solution = 7, [[1, 0, 1], [0, 1, 0]]

	example3 = [
		[4, 3, 2, 1, 1, 6]
	] #Solution = 12, [1, 0, 1, 0, 0, 1]

	example4 = [
		[4, 3],
		[3, 1]
	]

	outn, grido = ActivityM3.find_whisperers(example4)
	print("Output:", outn)
	print_grid(grido)