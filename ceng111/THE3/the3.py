def pattern_search(pattern,image):
    angle=0
    for c in range(4):
        if konum_bulma(pattern,image)==[]:
            pattern = dondurme(pattern)
            angle = angle + 90
        else:
            return tuple(konum_bulma(pattern,image)+[angle])
    return False


def konum_bulma(pattern,image):

    pattern_yukseklik=len(pattern)
    pattern_genislik=len(pattern[0])
    image_yukseklik = len(image)
    image_genislik=len(image[0])

    for i in range(image_yukseklik-pattern_yukseklik+1):
        for j in range(image_genislik-pattern_genislik+1):
            icinde=True
            for k in range(pattern_yukseklik):
                for l in range(pattern_genislik):
                    if icinde:
                        if pattern[k][l] == image[i+k][j+l]:
                            icinde = True
                        else:
                            icinde=False
                            break
                if not icinde:
                    break

            if icinde:
                return [i,j]
    return []


def dondurme(pattern):
    pattern_yukseklik = len(pattern)
    pattern_genislik = len(pattern[0])
    list_dondu = []

    for a in range(pattern_genislik):
        str = ""
        for b in range(-1, -pattern_yukseklik - 1, -1):
            str += pattern[b][a]
        list_dondu.append(str)
    return list_dondu