# ProjectFB
[230905/ldh]
캐릭터 무한 점프 로직, 고정 카메라 뷰 이용 로직 구현  
장애물 관련해서 어떤식으로 spawn할지 회의 필요(ex. 완전히 랜덤으로 하는가? 또는 정해진 방식대로 미리 구현하는가?)  

[230906/phw]
MainLevel -> GameLevel로 변경  
MainLevel -> 메인화면으로 사용  
MainCharacter -> 메인화면에서 사용하는 캐릭터  
Obstacle -> Pipe로 사용(버그 수정중)  

[230906/ldh]
프로젝트 합치기, 브랜치 삭제 후 logic 브랜치 생성, 로직 변경은 해당 브랜치로 진행  
Keys.h 추가 : 키워드들을 모아 한곳에서 namespace로 관리, Keys:: 라고 치면 검색할 수 있게 이중 namespace로 구성(ex) TEXT("GameLevel") > Keys::LevelKeys::StartLevel 로 대체)  
MainCharacter : Obstacle과 Overlap 시 GameMode의 Gameover 로직 실행하도록 함수 델리게이트 연결  
Gameover : 단순히 GameoverWidget을 표시, 플레이어 입력 제한 필요  
GameoverWidget : Restart버튼 로직 구현 필요, Main버튼 클릭 시 GameLevel(처음화면)으로 돌아감  
