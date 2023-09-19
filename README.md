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

* 복구 이후 GameoverWidget이 오류가 있어 프로젝트 재시작 시 열리지 않음, 클래스 파일은 그대로지만 블루프린트 오류

[230911/phw]
@레벨마다 사용되는 클래스
- MainMap
  * MainGameMode : MainMap에서 MainCharacter 생성
  * MainCharacter : 메인화면에서 보여질 캐릭터
  * MainWidget : 메인화면에서 보여질 위젯
- GameMap
  * GameGameMode : GameMap에서 PlayerCharacter생성, GameOverWidget생성 (클래스명 변경 논의 필요)
  * PlayerCharacter : GameMap에서 조종될 캐릭터
  * Obstacle : 장애물
  * GameOverWidget : 게임 종료시 보여질 위젯

@모듈별 클래스
- ProjectFB : 프레젝트 전체에서 사용될 클래스
  * TempActor : ProjectFB 모듈을 보여주기 위한 클래스(추 후 삭제 예정)
  * Keys : 프레임워크용
- Characters : 액터, 폰, 캐릭터를 넣어둘 정리용 모듈
  * MainCharacter : MainMap에서 사용
  * PlayerCharacter : GameMap에서 사용
- GameModes : 게임모드 정리용 모듈
  * MainGameMode : MainMap에서 사용
  * GameGameMode : GameMap에서 사용
- Widgets : 위젯 정리용 모듈
  * MainWidget : Main화면에서 사용 위젯
  * GameOverWidget : GameMap에서 사용 위젯

[230919/ldh]  
- 프레임워크 수정(클래스 이름 협의 후 통일)  
GameMap > FlappyWhaleMap, GameGameMode > FlappyWhaleGameMode, MainCamera > FlappyWhaleCamera로 클래스명 변경  
- 스포너 오브젝트 풀 로직 수정  
장애물 소환 직후 풀에 추가됨, 이후 다시 함수를 호출하면 직전에 소환된 장애물의 bActive가 false에 해당되어  
풀에서 방금 소환된 장애물의 Pos를 다시 SpawnPos로 소환하는 버그 수정을 위해 bActive플래그의 기본값을 true로 설정  
- 스포너 로직 추가/수정(랜덤, 주기)  
-3~3범위의 랜덤값으로 spawnPos의 z값만 변경하여 랜덤위치 소환 로직 구현, 소환주기 1초로 하여 테스트, 정상작동 확인  
- 장애물 사양 변경  
Z축 Scale을 4 > 8로 변경, 위치는 +-300 > +-500으로 변경  
