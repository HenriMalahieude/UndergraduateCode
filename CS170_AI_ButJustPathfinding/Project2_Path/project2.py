from typing import List, Tuple
import heapq
#Note: it is not (x, y) organization, but inverse: (y, x) because I'm maintaining indexing parity

def print_grid(grid: List[List[str]]):
	for row in grid:
		for lmnt in row:
			if len(lmnt) != 2:
				print("", lmnt, end="")
			else:
				print(lmnt, end="")
			print(" ", end="")
		print()



def get_ends(grid: List[List[str]]) -> Tuple[Tuple[int, int], Tuple[int, int]]:
	start, goal = (-1, -1), (-1, -1)
	for y in range(len(grid)):
		for x in range(len(grid[0])):
			if grid[y][x] == "s":
				start = (y, x)
			elif grid[y][x] == "t":
				goal = (y, x)

	return start, goal

def manhanttan_distance(pos1: Tuple[int, int], pos2: Tuple[int, int]):
	dy = pos1[0] - pos2[0]
	dx = pos1[1] - pos2[1]
	return abs(dx) + abs(dy)

#Does not look at whether they've been marked with a number yet or not
def get_next_dir(grid: List[List[str]], pos: Tuple[int, int]):
	y, x = pos
	nposs = []

	if (x+1) < len(grid[0]) and grid[y][x+1] != "-1": #Right
		nposs.append((y, x+1))

	if (y+1) < len(grid) and grid[y+1][x] != "-1": #Down
		nposs.append((y+1, x))
	
	if (x-1) >= 0 and grid[y][x-1] != "-1": #Left
		nposs.append((y, x-1))

	if (y-1) >= 0 and grid[y-1][x] != "-1": #Up
		nposs.append((y-1, x))

	return nposs

def get_path_from_prev_matrix(prev_matrix: List[List[Tuple[int, int]]], end: Tuple[int, int]) -> List[Tuple[int, int]]:
	path = []
	cur = end
	while cur != (-1, -1):
		path.insert(0, cur)
		cur = prev_matrix[cur[0]][cur[1]]
		if (cur == (-1, -1)):
			break
	
	return path

class SearchAlgorithm:
	# Implement Uniform search
	@staticmethod
	def uniform_search(grid: List[List[str]]) -> List[Tuple[int, int]]:
		prev_matrix = [[(-1, -1) for _ in range(len(grid[0]))] for _ in range(len(grid))]

		start, goal = get_ends(grid)
		#count = 1
		hp = [(0, start)]; heapq.heapify(hp)
		visited = []
		def custom_dirs(pos):
			y, x = pos
			nposs = []

			if (y-1) >= 0 and grid[y-1][x] != "-1": #Up
				nposs.append((y-1, x))

			if (x-1) >= 0 and grid[y][x-1] != "-1": #Left
				nposs.append((y, x-1))

			if (y+1) < len(grid) and grid[y+1][x] != "-1": #Down
				nposs.append((y+1, x))

			if (x+1) < len(grid[0]) and grid[y][x+1] != "-1": #Right
				nposs.append((y, x+1))

			return nposs

		while len(hp) > 0 and hp[0][1] != goal:
			current = heapq.heappop(hp)
			cur_coord = cy, cx = current[1]
			#if grid[cy][cx] != "t" and grid[cy][cx] != "s":
			#	grid[cy][cx] = str(count)
			#	count += 1

			visited.append(cur_coord)

			n_posis = custom_dirs(cur_coord)
			for pos in n_posis:
				hready = (current[0] + 1, pos)
				if pos not in visited and hready not in hp:
					heapq.heappush(hp, hready)
					prev_matrix[pos[0]][pos[1]] = cur_coord
		
		return get_path_from_prev_matrix(prev_matrix, goal) if (len(hp) > 0 and hp[0][1] == goal) else []

	# Implement Depth First Search
	@staticmethod
	def dfs(grid: List[List[str]])  -> List[Tuple[int, int]]: #Passes 1->5
		start, goal = get_ends(grid)
		#count = 1
		path = [start]
		used = []
		while len(path) > 0 and path[-1] != goal:
			current = path[-1]
			new_posis = get_next_dir(grid, current) #Get a list of next positions
			choosable_pos = []
			for elem in new_posis: #Remove all the ones we've already visited
				if not (elem in used) and not (elem in path):
					choosable_pos.append(elem)
			
			if (goal in choosable_pos):
				path.append(goal)
				break
			
			choosable_pos.reverse() #Because LIFO procedures? I'm sorry that doesn't make sense to me
			chose_dir = (-1, -1) if len(choosable_pos) <= 0 else choosable_pos[0]

			if chose_dir[0] != -1 and chose_dir[1] != -1: #we chose a proper direction
				ny, nx = chose_dir
				path.append(chose_dir) #add to path
				if grid[ny][nx] == "t":
					break
				#grid[ny][nx] = str(count) #mark path
				#count += 1
			else: #We need to backtrack because no choosable position to go to
				path.pop() #remove current, is definitely not part of path
				used.append(current) #mark as visited to avoid confusion
		
		return path

	# Implement Breadth First Search
	@staticmethod
	def bfs(grid: List[List[str]]) -> List[Tuple[int, int]]: #Passes 1->5
		prev_matrix = [[(-1, -1) for _ in range(len(grid[0]))] for _ in range(len(grid))]

		start, goal = get_ends(grid)
		#count = 1
		q = [start]
		visited = []
		while len(q) > 0 and q[0] != goal:
			current = q.pop(0)
			cy, cx = current
			#if grid[cy][cx] != "s" and grid[cy][cx] != "t":
			#	grid[cy][cx] = str(count)
			#	count += 1

			visited.append(current)
			new_posis = get_next_dir(grid, current)

			for pos in new_posis:
				y, x = pos
				if not (pos in visited) and not (pos in q):
					q.append(pos)
					prev_matrix[y][x] = current
		
		return get_path_from_prev_matrix(prev_matrix, goal) if (len(q) > 0 and q[0] == goal) else []
					
	# Implement Best First Search
	@staticmethod
	def best_first_search(grid: List[List[str]]) -> List[Tuple[int, int]]:
		prev_matrix = [[(-1, -1) for _ in range(len(grid[0]))] for _ in range(len(grid))]
		
		start, goal = get_ends(grid)
		hp = []; heapq.heappush(hp, (manhanttan_distance(start, goal), start))
		visited = []
		#count = 1
		while len(hp) > 0 and hp[0][1] != goal:
			current = heapq.heappop(hp)
			cur_coord = cy, cx = current[1]
			#if grid[cy][cx] != "t" and grid[cy][cx] != "s":
			#	grid[cy][cx] = str(count)
			#	count += 1

			visited.append(cur_coord)
			n_posis = get_next_dir(grid, cur_coord)
			for npos in n_posis:
				hready = (manhanttan_distance(npos, goal), npos)
				if npos not in visited and hready not in hp:
					heapq.heappush(hp, hready)
					prev_matrix[npos[0]][npos[1]] = cur_coord

		return get_path_from_prev_matrix(prev_matrix, goal) if (len(hp) > 0 and hp[0][1] == goal) else []

	# Implement A* Search
	@staticmethod
	def a_star_search(grid: List[List[str]]) -> List[Tuple[int, int]]:
		prev_matrix = [[(-1, -1, -1) for _ in range(len(grid[0]))] for _ in range(len(grid))]

		start, goal = get_ends(grid) #goal = (y, x), start = (y, x)
		hp = [(manhanttan_distance(start, goal), start[0], start[1])]; heapq.heapify(hp)
		visited = []
		#count = 1

		coord = (-1, -1)
		while len(hp) > 0 and coord != goal:
			current = heapq.heappop(hp)
			coord = cy, cx, = (current[1], current[2])
			m_cost = current[0] - manhanttan_distance(goal, coord)

			if (coord in visited):
				continue

			visited.append(coord)
			if (grid[cy][cx] == "t"):
				break

			#print_grid(grid)
			#print("Currently at:", coord)
			#grid[cy][cx] = "V"

			n_posis = get_next_dir(grid, coord)
			#print("\tNext Possible are:")
			for npos in n_posis:
				hready = (manhanttan_distance(goal, npos) + m_cost + 1, npos[0], npos[1])
				if hready not in hp and npos not in visited and prev_matrix[npos[0]][npos[1]] == (-1, -1):
					#print("\t\t", npos)
					heapq.heappush(hp, hready)
					prev_matrix[npos[0]][npos[1]] = coord
			#input("\n")
			
		return get_path_from_prev_matrix(prev_matrix, goal) if (coord == goal) else []
	
	# Implement Greedy Search
	@staticmethod
	def greedy_search(grid: List[List[str]]) -> List[Tuple[int, int]]: #Passes 1->5
		start, goal = get_ends(grid)
		#count = 1
		cur_dist = manhanttan_distance(start, goal)
		path = [start]
		while path[-1] != goal:
			cur_coord = path[-1]
			dirs = get_next_dir(grid, cur_coord)
			dir_ichose = (-1, -1)
			dir_idist = 100000000
			for n_coord in dirs:
				dd = manhanttan_distance(n_coord, goal)
				if dd < dir_idist and dd < cur_dist:
					dir_idist = dd
					dir_ichose = n_coord

			if dir_ichose[0] != -1 and dir_ichose[1] != -1:
				path.append(dir_ichose)
				ny, nx = dir_ichose
				cur_dist = dir_idist
				#if grid[ny][nx] != "t":
				#	grid[ny][nx] = str(count)
				#	count += 1
			else:
				break
		
		return path if path[-1] == goal else []

if __name__ == "__main__":
	example1 = [
		['0', '0', '0', '0'],
		['0', '-1', '-1', 't'],
		['s', '0', '-1', '0'],
		['0', '0', '0', '-1']
	]

	example2 = [
		['s', '0', '0', '0', '-1', '-1', '-1', '-1'],
		['0', '0', '0', '0', '0', '-1', '-1', '-1'],
		['-1', '-1', '0', '-1', '-1', '0', '0', '0'],
		['-1', '0', '0', '0', '0', '0', '0', 't']
	]

	example3 = [
		['s', '0', '0', '-1', '0'],
		['0', '-1', '0', '-1', 't'],
		['0', '-1', '0', '0', '0'],
		['0', '0', '0', '-1', '0'],
		['0', '-1', '-1', '-1', '0'],
	]

	example4 = [
		['s', '0', '0', '0', '0'],
		['-1', '-1', '0', '0', '0'],
		['t', '-1', '0', '0', '0'],
		['-1', '0', '0', '-1', '0'],
		['0', '-1', '0', '-1', '0']
	]

	example5 = [
		['0', '0', '0', '-1', '0'],
		['0', '0', '0', '-1', '0'],
		['s', '0', '0', '0', '0'],
		['0', '0', '0', '-1', 't'],
		['0', '0', '0', '-1', '0'],
	]
	
	example6 = [
		["0", "0", "-1", "0", "0", "0", "0", "0", "0", "-1"],
		["-1", "0", "-1", "0", "t", "-1", "0", "0", "-1", "-1"],
		["-1", "0", "-1", "0", "0", "0", "0", "-1",  "0", "0"],
		["-1", "0", "0", "0", "0", "0", "0", "-1", "0", "-1"],
		["-1", "0", "-1", "0", "-1", "-1", "0", "-1", "-1", "-1"],
		["-1", "0", "0", "0", "-1", "0", "0", "-1", "0", "-1"],
		["-1", "0", "-1", "-1", "-1", "-1", "0", "0", "0", "-1"],
		["-1", "0", "0", "-1", "s", "0", "0", " 0", "-1",  "0"],
		["0", "-1", "0", "0", "0", "0", "0", "-1", "-1", "0"],
		["0", "-1", "0", "0", "0", "0", "0", "0", "0", "0"],
	]

	example7 = [
		["0",  "-1", "-1", "-1",  "0", "-1", "-1", "-1", "-1", "-1"],
		["-1",  "0", "-1", "-1",  "0", "-1",  "0",  "0",  "0",  "0"],
		[" 0",  "0",  "0", "-1", "-1",  "0",  "0",  "0",  "0",  "0"],
		["-1",  "0",  "0", "-1",  "0",  "0",  "0", "-1",  "0", "-1"],
		["-1",  "0",  "0",  "0", "-1",  "t",  "0",  "0", "-1",  "0"],
		["-1",  "0",  "s", "-1",  "0",  "0", "-1",  "0",  "0", "-1"],
		["0",   "0",  "0",  "0", "-1",  "0",  "0",  "0",  "0", "-1"],
		["-1", "-1", "-1",  "0",  "0",  "0",  "0",  "0",  "0",  "0"],
		["-1", "-1", "-1",  "0", "-1", "-1",  "0", "-1", "-1",  "0"],
		["-1",  "0", "-1",  "0",  "0", "-1", "-1",  "0",  "0",  "0"],
	]

	example8 = [
		["-1", "0", "0", "0", "0", "0", "-1", "0", "0", "-1"],
		["-1", "-1", "0", "0", "-1", "-1", "0", "0", "-1", "0"],
		["0", "-1", "-1", "0", "-1", "0", "0", "0", "-1", "0"],
		["-1", "-1", "0", "0", "0", "t", "-1", "-1", "0", "0"],
		["0", "0", "-1", "-1", "0", "0", "0", "-1", "-1", "0"],
		["0", "0", "0", "-1", "-1", "0", "0", "0", "-1", "0"],
		["0", "0", "0", "0", "0", "0", "-1", "-1", "-1", "-1"],
		["s", "-1", "-1", "-1", "-1", "-1", "0", "-1", "0", "0"],
		["0", "-1", "-1", "0", "-1", "0", "-1", "0", "-1", "0"],
		["-1", "0", "-1", "0", "0", "0", "0", "0", "-1", "-1"]
	]

	path = SearchAlgorithm.a_star_search(example6)
	print_grid(example6)
	print("Length:", len(path))
	print(path)
