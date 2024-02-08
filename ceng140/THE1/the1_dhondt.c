#include <stdio.h>

int main() {
    float oy_sayilari[26];
    float guncel_mv_adet[26],hedef_mv[26];
    int parti_sayisi,koltuk_sayisi,partiler[26];
    int i,j,k,s,q;
    int hakeden,hakeden_index;
    int parti_will_be_printed,parti_will_be_printed_index;
    char letter;
    scanf("%d %d",&parti_sayisi,&koltuk_sayisi);
    for(i=0;i<parti_sayisi ;i++){
        scanf("%f",&oy_sayilari[i]);
    }
    for(q=0;q<parti_sayisi;q++){
        guncel_mv_adet[q]=0.0;
        hedef_mv[q]=1.0;
    }
    
    
    for(j=65;j<65+parti_sayisi;j++){
        letter = j;
        partiler[j-65]=letter;
    }
    while (koltuk_sayisi){
        hakeden=oy_sayilari[0];
        hakeden_index=0;
        for(k=1;k<parti_sayisi;k++){
            if (oy_sayilari[k]/hedef_mv[k]>hakeden/hedef_mv[hakeden_index]){
                hakeden=oy_sayilari[k];
                hakeden_index=k;
            }
            else if (oy_sayilari[k]/hedef_mv[k]==hakeden/hedef_mv[hakeden_index]){
                if(oy_sayilari[k]>oy_sayilari[hakeden_index]){
                    hakeden=oy_sayilari[k];
                    hakeden_index=k;
                }
            }
        }
        guncel_mv_adet[hakeden_index]++;
        hedef_mv[hakeden_index]++;
        koltuk_sayisi--;
    }
    for(i=0;i<parti_sayisi;i++){
        parti_will_be_printed=guncel_mv_adet[0];
        parti_will_be_printed_index=0;
        for (s=1;s<parti_sayisi;s++){
            if (parti_will_be_printed<guncel_mv_adet[s]){
                parti_will_be_printed=guncel_mv_adet[s];
                parti_will_be_printed_index=s;
            }
        }
        if(parti_will_be_printed!=0){
            printf("%c: %d\n",partiler[parti_will_be_printed_index],parti_will_be_printed);
            guncel_mv_adet[parti_will_be_printed_index]=0;
        }
    }
    return 0;
}