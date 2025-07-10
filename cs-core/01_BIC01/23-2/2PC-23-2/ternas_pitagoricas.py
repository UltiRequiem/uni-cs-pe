def pytagoric_pairs_up_to(top: int):
    pairs = []

    for number in range(1,top):
        for x in range(1,number):
            for y in range(2, x): # y alwayss less than x
                if x**2 + y**2 == number**2:
                    
                    is_repeated = False

                    for pair in pairs:
                        if x % pair[0] == 0 and y % pair[1] == 0:
                            is_repeated = True
                            

                    if not is_repeated:
                        pairs.append([x,y, number])

    return pairs

def main():
    cota = input("Ingrese una cota: ")
    pairs_found = pytagoric_pairs_up_to(int(cota))
    total_pairs = len(pairs_found)

    if total_pairs> 0:
        print(f'{total_pairs} pairs were found!')
        for pair in pairs_found:
         print(pair)
    else:
        print("No se encontro ningun par que cumpla en ese rango.")

if __name__ == "__main__":
    main()
