from typing import List, Tuple

def get_value(row, index):
    if index < 0 or index >= len(row):
        return 0
    
    return row[index]

def set_value(m, row, index, val):
    if index < 0 or index >= m:
        return

    if index >= len(row):
        row.append(val)
        return
    
    row[index] = val

class ActivityM3:
    @staticmethod
    def find_whisperers_1d(row: List[int]) -> Tuple[int, List[int]]:
        m = len(row)
        output = []
        score = 0
    
        i = 0
        while i < m:
            u = get_value(row, i - 3)
            v = get_value(row, i - 2)
            w = get_value(row, i - 1)
            x = get_value(row, i)
            y = get_value(row, i + 1)
            z = get_value(row, i + 2)

            if (v == 0 and w == 0) or (v == 1 and w == 0): #Catch first normal case, and starting case
                if (x + z) > y:
                    set_value(m, output, i  , 1); score += x #x = 1
                    set_value(m, output, i+1, 0);            #y = 0
                    set_value(m, output, i+2, 1); score += z #z = 1
                else: # (x + z) <= y
                    set_value(m, output, i  , 0)             #x = 0
                    set_value(m, output, i+1, 1); score += y #y = 1
                    set_value(m, output, i+2, 0)             #z = 0
            else: #v == 0 and w == 1
                if (x + z) > y: #can we set 101?
                    if w >= x:
                        set_value(m, output, i  , 0)             #x = 0
                        set_value(m, output, i+1, 0)             #y = 0
                        set_value(m, output, i+2, 1); score += z #z = 1
                    else: #w < x
                        if u == 0: #Means we can take this score
                            set_value(m, output, i-2, 1); score += v #v = 1

                        set_value(m, output, i-1, 0); score -= w #w = 0 bc w < x
                        set_value(m, output, i  , 1); score += x #x = 1 bc w < x
                        set_value(m, output, i+1, 0)             #y = 0
                        set_value(m, output, i+2, 1); score += z #z = 1
                else: #(x + z) < y
                    set_value(m, output, i  , 0)             #x = 0
                    set_value(m, output, i+1, 1); score += y #y = 1
                    set_value(m, output, i+2, 0)             #z = 0

            i += 3 #Context window of 3, plus look behind of 3
            #print("Current Score:", score)
            #print("In_Grid:", row)
            #print("Out_Grid:", output)
            #print("Iteration:", i)
            #input("------\n")

        return score, output
            

if __name__ == "__main__":
    example0 = [5,6]
    example1 = [1,2,4]
    example2 = [4,3,2,1,1,6]
    example3 = [1,2,3,4,5,6]

    score, result = ActivityM3.find_whisperers_1d(example2)
    print(score, result)
