from typing import List, Tuple

class ActivityM3:
    @staticmethod
    def find_whisperers_1d(row: List[int]) -> Tuple[int, List[int]]:
        m = len(row)
        output = []
        score = 0
    
        i = 0
        while i < m:
            up = i - 3; u = 0 if up < 0 else row[up]
            vp = i - 2; v = 0 if vp < 0 else row[vp]
            wp = i - 1; w = 0 if wp < 0 else row[wp]
            xp = i    ; x = row[xp]
            yp = i + 1; y = 0 if yp >= len(row) else row[yp]
            zp = i + 2; z = 0 if zp >= len(row) else row[zp]

            if (v == 0 and w == 0) or (v == 1 and w == 0): #Catch first normal case, and starting case
                if (x + z) > y: #Set xyz = 101
                    output.append(1); score += x
                    if yp < len(row):
                       output.append(0)
                    
                    if zp < len(row):
                        output.append(1); score += z
                else: # (x + z) <= y || Set xyz = 010
                    output.append(0)
                    
                    if yp < len(row):
                        output.append(1); score += y
                    
                    if zp < len(row):
                        output.append(0)
            else: #v == 0 and w == 1
                if (x + z) > y: #can we set 101?
                    if w >= x: #No we can only set 001
                        output.append(0)
                        if yp < len(row):
                            output.append(0)
                        
                        if zp < len(row):
                            output.append(1); score += z

                    else: #w < x || Yes we can set 101
                        if u == 0: #Means we can add this score
                            output[vp] = 1; score += v #v = 1

                        output[wp] = 0; score -= w               #w = 0 bc w < x
                        output.append(1); score += x #x = 1 bc w < x

                        if yp < len(row):
                            output.append(0)
                        
                        if zp < len(row):
                            output.append(1); score += z
                else: #(x + z) < y || Set 010
                    output.append(0)

                    if yp < len(row):
                        output.append(1); score += y
                    
                    if zp < len(row):
                        output.append(0)

            i += 3 #Context window of 3, plus look behind of 3

        return score, output
            

if __name__ == "__main__":
    example0 = [5,6]
    example1 = [1,2,4]
    example2 = [4,3,2,1,1,6]
    example3 = [1,2,3,4,5,6]

    score, result = ActivityM3.find_whisperers_1d(example3)
    print(score, result)
