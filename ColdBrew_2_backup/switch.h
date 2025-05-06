// switch.h
#ifndef SWITCH_H
#define SWITCH_H
// 커피머신 세정
void orderCoffeeCleaning();
// 커피머신 하단부 세정
void orderCoffeeLowerCleaning();
// 디카페인 사이클 세정
void orderDecafCycleCleaning();
// 콜드브루 본체 세정
void orderColdBrewCleaning();
// 콜드브루 라인1 세정
void orderColdBrewLineCleaningOne();
// 콜드브루 라인2 세정
void orderColdBrewLineCleaningTwo();
// 브루드커피 추출
void orderBrewedExtraction();
// 브루드커피 냉각
void orderBrewedCooling();
// 브루드커피 이송
void orderBrewedTransfer();
// 콜드브루 추출
void orderColdBrewExtraction();
// 콜드브루 추출
void orderColdBrewCooling();
// 콜드브루 이송
void orderColdBrewTransfer();
// 디카페인 추출
void orderDecafExtraction();
// 디카페인 냉각
void orderDecafCooling();
// 디카페인 이송
void orderDecafTransfer();
// 디카페인 냉장고에서 이동
void orderDecafTransferFromFridge();
#endif // SWITCH_H