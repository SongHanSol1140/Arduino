// switch.h
#ifndef SWITCH_H
#define SWITCH_H
// 1. 커피머신 세정
void orderCoffeeCleaning();
// 2. 커피머신 하단부 세정
void orderCoffeeLowerCleaning();
// 3. 디카페인 사이클 세정
void orderDecafCycleCleaning();
// 4. 콜드브루 이송(판매)
void orderColdeBrewSell();
// 5. 콜드브루 본체 세정
void orderColdBrewCleaning();
// 6. 콜드브루 라인1 세정
void orderColdBrewLineCleaningOne();
// 7. 콜드브루 라인2 세정
void orderColdBrewLineCleaningTwo();
// 8. 브루드커피 추출
void orderBrewedExtraction();
// 9. 브루드커피 냉각
void orderBrewedCooling();
// 10. 브루드커피 이송
void orderBrewedTransfer();
// 11. 콜드브루 추출
void orderColdBrewExtraction();
// 12. 콜드브루 추출
void orderColdBrewCooling();
// 13. 콜드브루 이송
void orderColdBrewTransfer();
// 14, 디카페인 추출
void orderDecafExtraction();
// 15. 디카페인 냉각
void orderDecafCooling();
// 16. 디카페인 이송
void orderDecafTransfer();
// 17. 디카페인 냉장고에서 이동
void orderDecafTransferFromFridge();
#endif // SWITCH_H