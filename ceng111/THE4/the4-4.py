def construct_forest(Defs):
    bosluksuz_list=space_deleter(Defs)
    datumlar=datum_bulan(bosluksuz_list)
    all_trees=[]

    for m in range(len(datumlar)):
        all_trees += [datumlardan_yapraklara(datumlar[m],bosluksuz_list)]
    return all_trees

def operator_konum_bulucu(string):
    for t in range(len(string)):
        if string[t]=="+" or string[t]=="-" or string[t]=="*" or string[t]=="^":
            return int(t)
        else:
            pass


def space_deleter(ham_list):
#listedeki boşlukları silmece
    listin_uzunlugu = len(ham_list)
    for i in range(listin_uzunlugu):
        if " " in ham_list[i]:
            ham_list[i] = ham_list[i].replace(" ", "")
        else:
            pass
    return ham_list

def datum_bulan(bosluksuz_list):
    datumlar=[]
    for k in range(len(bosluksuz_list)):
        q=0
        for l in range(len(bosluksuz_list)):
            if bosluksuz_list[k][0] not in bosluksuz_list[l][4:]:
                q +=1
        if len(bosluksuz_list)==q:
            datumlar += [bosluksuz_list[k]]
    return datumlar


def fonksiyonu_listten_alıp_getiren(ehue,list_x):
    for u in range(len(list_x)):
        if str(ehue)==list_x[u][0]:
            return list_x[u]

def datumlardan_yapraklara(datum,list_x):

    if len(datum)<=10:
        return [str(datum[0]) , str(datum[operator_konum_bulucu(datum)]) , [str(datum[5:operator_konum_bulucu(datum)])] , [str(datum[operator_konum_bulucu(datum)+1:])]]

#sol fonksiyonken    sağ sayı veya x
    elif datum[6]=="(" and len(datum)<=13:
        return [str(datum[0]) , str(datum[operator_konum_bulucu(datum)]) , datumlardan_yapraklara(fonksiyonu_listten_alıp_getiren(datum[5],list_x),list_x) , [str(datum[operator_konum_bulucu(datum)+1:]) ] ]

#sağ fonksiyonken    sol sayı veya x

    elif datum[operator_konum_bulucu(datum)+2]=="(" and len(datum)<=13:
        return [str(datum[0]) , str(datum[operator_konum_bulucu(datum)]) , [str(datum[5:operator_konum_bulucu(datum)])] , datumlardan_yapraklara(fonksiyonu_listten_alıp_getiren(datum[-4],list_x),list_x)]

#iki taraf da fonksiyonken

    elif len(datum)==14:
        return [str(datum[0]) , str(datum[operator_konum_bulucu(datum)]) , datumlardan_yapraklara(fonksiyonu_listten_alıp_getiren(datum[5],list_x),list_x) , datumlardan_yapraklara(fonksiyonu_listten_alıp_getiren(datum[-4],list_x),list_x)]
