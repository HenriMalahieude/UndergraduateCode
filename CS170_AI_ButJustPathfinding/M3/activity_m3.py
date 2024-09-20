#Depth-First Search Version
from typing import List, Tuple

def print_grid(grid: List[List[int]]):
	for row in grid:
		print(*row)

def cardinal_dirs(coord: Tuple[int, int], m: int, n: int) -> List[Tuple[int, int]]:
	r, c = coord
	dirs = []

	if (r - 1) >= 0: #up
		dirs.append((r-1, c))

	if (r + 1) < m: #down
		dirs.append((r+1, c))
	
	if (c - 1) >= 0: #left
		dirs.append((r, c-1))

	if (c + 1) < n: #right
		dirs.append((r, c+1))

	return dirs

def generate_empty(m: int, n: int) -> List[List[int]]:
	return [[0 for _ in range(n)] for _ in range(m)]

def is_full(x):
	for i in range(len(x)):
		for j in range(len(x[0])):
			if x[i][j] == 0:
				return False

	return True

def get_visit(using, m, n):
	visitable = []
	for i in range(m):
		for j in range(n):
			visitable.append((i, j)) 

	for coord in using:
		visitable.remove(coord)
		surround = cardinal_dirs(coord, m, n)
		for scoord in surround:
			if scoord in visitable:
				visitable.remove(scoord)

	return visitable

class ActivityM3:
	@staticmethod
	def find_whisperers(grid: List[List[int]]) -> Tuple[int, List[List[int]]]:
		m, n = len(grid), len(grid[0])
		using = [] #This is a sort of stack if you will
		search_tree = []
		search_tree.append(generate_empty(m, n))
		
		best_using = []
		best_score = -1

		cur_lyr = 0
		cur_score = 0
		while True:
			#print("Currently Best Score:", best_score)
			#print("Currently Best Stack:", best_using, "\n")
			#print("Current Tree Layer:", cur_lyr)
			#print("Current Score:", cur_score)
			#print_grid(search_tree[cur_lyr])
			
			#Select next to visit
			visitable = get_visit(using, m, n)
			#print("Visitable:", len(visitable))
			if len(visitable) <= 0: #We are at the bottom of the tree
				#print("nothing is visitable anymore, going up the tree\n")
				#print(best_score, "<", cur_score)
				if best_score < cur_score:
					#print("found a better score than", best_score, "setting it to", cur_score)
					best_using = using.copy()
					best_score = cur_score

				search_tree[cur_lyr] = generate_empty(m, n)
				cur_lyr -= 1
				rr, cc, = last_coord = using.pop()
				cur_score -= grid[rr][cc]
				continue

			next_coord = (-1, -1)
			for coord in visitable:
				r, c = coord
				if search_tree[cur_lyr][r][c] == 0:
					next_coord = coord
					#print("Next Coordinate: ", next_coord)
					break

			#print("next", next_coord)
			#Determine what to do with said coord
			if (next_coord[0] == -1 or next_coord[1] == -1): #We've fully explored this tree branch
				#print("we've completely visited all tree branches, going up the tree\n")
				search_tree[cur_lyr] = generate_empty(m, n)
				cur_lyr -= 1
				if cur_lyr <= 0 and is_full(search_tree[0]):
					break
				
				rr, cc = last_coord = using.pop()
				cur_score -= grid[rr][cc]
				continue
			
			search_tree[cur_lyr][next_coord[0]][next_coord[1]] = 1 #We have yet to explore this tree branch
			cur_lyr += 1
			using.append(next_coord)
			cur_score += grid[next_coord[0]][next_coord[1]]
			if len(search_tree) < (cur_lyr+1):
				search_tree.append(generate_empty(m, n))
			
			#print("New Stack:", using)
			#print("-----------------")
			#input("\n")

		#Reconstruct a grid of those chosen
		sending = generate_empty(m, n)
		for coord in best_using:
			sending[coord[0]][coord[1]] = 1
		
		return best_score, sending

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
	] #Solution = 6, [[0, 1], [1, 0]]

	outn, grido = ActivityM3.find_whisperers(example4)
	print("Output:", outn)
	print_grid(grido)