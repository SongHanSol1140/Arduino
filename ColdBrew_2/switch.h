// switch.h
#ifndef SWITCH_H
#define SWITCH_H
// 커피머신 세정
void orderCoffeeMachineCleaning();
// 커피머신 하단부 세정
void orderCoffeeMachineLowerCleaning();
// 디카페인 사이클 세정
void orderCfCycleCleaning();
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
void orderCfExtraction();
// 디카페인 냉각
void orderCfCooling();
// 디카페인 이송
void orderCfTransfer();
// 보틀에서 이동
void orderBottleTransfer();
#endif // SWITCH_H