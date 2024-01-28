from typing import List, Tuple
#Note: it is not (x, y) organization, but inverse: (y, x) because we love minecraft

def print_grid(grid: List[List[str]]):
	for row in grid:
		print(' '.join(row))

def get_ends(grid: List[List[str]]) -> Tuple[Tuple[int, int], Tuple[int, int]]:
	start, goal = (-1, -1), (-1, -1)
	for y in range(len(grid)):
		for x in range(len(grid[0])):
			if grid[y][x] == "s":
				start = (y, x)
			elif grid[y][x] == "t":
				goal = (y, x)

	return start, goal

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

class SearchAlgorithm:
	# Implement Uniform search
	@staticmethod
	def uniform_search(grid: List[List[str]]) -> Tuple[int, List[List[str]]]:
		# Your code here
		pass

	# Implement Depth First Search
	@staticmethod
	def dfs(grid: List[List[str]]) -> Tuple[int, List[List[str]]]: #Passes 1->5
		start, goal = get_ends(grid)
		count = 1
		path = [start]
		used = []
		while len(path) > 0 and path[-1] != goal:
			current = path[-1]
			new_posis = get_next_dir(grid, current) #Get a list of next positions
			choosable_pos = []
			for elem in new_posis: #Remove all the ones we've already visited
				if not (elem in used) and not (elem in path):
					choosable_pos.append(elem)
			
			choosable_pos.reverse() #Because LIFO procedures? I'm sorry that doesn't make sense to me
			chose_dir = (-1, -1) if len(choosable_pos) <= 0 else choosable_pos[0]

			if chose_dir[0] != -1 and chose_dir[1] != -1: #we chose a proper direction
				ny, nx = chose_dir
				path.append(chose_dir) #add to path
				if grid[ny][nx] == "t":
					break
				grid[ny][nx] = str(count) #mark path
				count += 1
			else: #We need to backtrack because no choosable position to go to
				path.pop() #remove current, is definitely not part of path
				used.append(current) #mark as visited to avoid confusion
		
		return ((len(path) > 0 and path[-1] == goal), grid)

	# Implement Breadth First Search
	@staticmethod
	def bfs(grid: List[List[str]]) -> Tuple[int, List[List[str]]]:
		start, goal = get_ends(grid)
		count = 1
		q = [start]
		visited = []
		while len(q) > 0 and q[0] != goal:
			#input("Continue\n")
			current = q.pop(0)
			cy, cx = current
			#print(f"Current: {current}")
			if grid[cy][cx] != "s" and grid[cy][cx] != "t":
				#print("adding 1")
				grid[cy][cx] = str(count)
				count += 1

			visited.append(current)
			new_posis = get_next_dir(grid, current)

			for pos in new_posis:
				y, x = pos
				if not (pos in visited) and not (pos in q):
					q.append(pos)
			
		return ((len(q) > 0 and q[0] == goal), grid)
					
	# Implement Best First Search
	@staticmethod
	def best_first_search(grid: List[List[str]]) -> Tuple[int, List[List[str]]]:
		# Your code here
		pass

	# Implement A* Search
	@staticmethod
	def a_star_search(grid: List[List[str]]) -> Tuple[int, List[List[str]]]:
		# Your code here
		pass

	# Implement Greedy Search
	@staticmethod
	def greedy_search(grid: List[List[str]]) -> Tuple[int, List[List[str]]]:
		# Your code here
		pass

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

	found, final_state = SearchAlgorithm.bfs(example5)

	if found == 1:
		print("Target found!")
	else:
		print("Target not found.")

	print_grid(final_state)
