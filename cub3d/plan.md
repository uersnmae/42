[ .cub 파일 ] 
      ↓
[ Parser + Validator ]    // 이미 구현되어 있다고 가정
      ↓
[ Game Context(t_game) 초기화 ] 
      ↓
[ FSM (의사결정) ]  --> 내가함
      ↓
[ Physics Engine ]       // 좌표 갱신·충돌 처리 (예: physics_update()) -->
      ↓
[ Rendering Engine ]     // 화면에 그리기 (예: render_frame())
      ↓
[ 루프 반복 ]              // 키 입력, FSM 이벤트 생성 → FSM 실행 → 물리 연산 → 렌더링 → 키 입력 ...
