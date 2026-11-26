# 💻 Azure VM 기반 Mini OS

## 📌 소개
Microsoft Azure의 Linux VM 환경에서 C 언어를 활용해 **가상 파일 시스템과 Linux Shell을 구현한 Mini OS 프로젝트**입니다.  
Parent-Child-Sibling 기반의 트리 자료구조를 활용하여 파일 및 디렉터리를 관리하고, 주요 Linux 명령어의 동작을 구현하였습니다.

- **개발 기간**: 2026.05.08 ~ 2026.06.10
- **프로젝트 유형**: 운영체제 교과목 팀 프로젝트

## 👥 팀 구성 및 역할
- 개발 인원: 5명
- Azure VM 환경 구축 및 서버 관리
- Interactive Shell 및 가상 파일 시스템 구현
- 파일 및 디렉터리 관련 명령어 구현
- 파일 검색 및 내용 처리 명령어 구현
- 시스템 통합 및 테스트

## 🛠️ 기술 스택
- **Language**: C
- **OS**: Ubuntu 22.04 LTS
- **Cloud**: Microsoft Azure VM
- **Remote Access**: SSH
- **Concurrency**: POSIX Threads, Mutex
- **Data Structure**: Parent-Child-Sibling Tree

## 🚀 주요 기능
- Interactive Shell 기반 사용자 명령어 입력 및 처리
- 트리 자료구조 기반 가상 파일 시스템 구현
- 파일 및 디렉터리 목록, 현재 경로 확인 (`ls`, `pwd`)
- 디렉터리 생성 및 경로 이동 (`mkdir`, `cd`)
- 파일 및 디렉터리 이동, 이름 변경, 삭제 (`mv`, `rm`)
- 파일 내용 출력 및 문자열 검색 (`cat`, `grep`)
- 문자열 출력 및 파일 리다이렉션 (`echo`)
- 파일 소유자 변경 및 상태 정보 조회 (`chown`, `stat`)
- 파일 검색 및 디렉터리 계층 구조 출력 (`find`, `tree`)
- 멀티스레딩 및 Mutex 기반 공유 자원 동기화
- 파일 시스템 상태 저장 및 복원

## 👩‍💻 개인 기여 및 담당 역할 (@240nayoung)
- `rm`: 파일 및 디렉터리 삭제, 멀티스레딩 기반 다중 삭제
- `mv`: 파일 및 디렉터리 이동, 이름 변경
- `echo`: 문자열 출력 및 파일 리다이렉션
- 프로젝트 최종 보고서 작성 참여

### rm - 파일 및 디렉터리 삭제
- 파일 및 디렉터리 삭제 기능 구현
- `-r`, `-f`, `-rf` 옵션 처리
- POSIX Threads를 활용한 삭제 대상별 스레드 생성
- Mutex를 활용한 공유 파일 시스템 접근 동기화
- 재귀적 디렉터리 삭제 및 동적 메모리 해제
- 루트 디렉터리 삭제 방지 및 예외 처리

### mv - 파일 및 디렉터리 이동, 이름 변경
- 파일 및 디렉터리 이동 기능 구현
- 절대 경로 및 상대 경로 기반 대상 탐색
- 트리 노드의 연결 관계 변경을 통한 파일 이동
- 파일 및 디렉터리 이름 변경
- 중복 이름 검사 및 잘못된 경로에 대한 예외 처리
- Mutex 기반 공유 자원 보호

### echo - 문자열 출력 및 리다이렉션
- 사용자 입력 문자열 출력 기능 구현
- `>` 연산자를 활용한 파일 내용 덮어쓰기
- `>>` 연산자를 활용한 파일 내용 추가
- 대상 파일이 존재하지 않을 경우 신규 파일 생성
- 명령어 인자 분석 및 예외 처리

### 협업 및 보고서 작성
- Azure Linux VM에 SSH로 접속하여 원격 개발
- 개별 명령어 모듈 통합 및 기능 검증 참여
- 담당 명령어의 구현 방식 및 실행 결과 문서화

## 📸 실행 화면
<details>
  <summary><b>rm 명령어 실행 결과</b></summary>
  
  ### 1. 초기 디렉터리 구조
  <img width="366" height="225" alt="image" src="https://github.com/user-attachments/assets/094b7f4b-29cb-459c-9e1c-cd001b5d085c" />

  ### 2. 일반 파일 삭제
  <img width="384" height="276" alt="image" src="https://github.com/user-attachments/assets/ab675001-c381-45bb-a698-897d343a38d3" />

  ### 3. 존재하지 않는 파일 삭제 시 예외 처리
  <img width="684" height="51" alt="image" src="https://github.com/user-attachments/assets/07e453c8-8eb0-4d95-aeb3-8fe1b3d7a400" />
  
  ### 4. -r 옵션 없이 디렉터리 삭제 시 예외 처리
  <img width="521" height="48" alt="image" src="https://github.com/user-attachments/assets/6969f7cc-d037-46bd-9e23-f657078bf98a" />

  ### 5. 재귀적 디렉터리 삭제 (-r)
  <img width="324" height="202" alt="image" src="https://github.com/user-attachments/assets/190c5913-c997-4e46-9a85-84cc6dd79999" />

  ### 6. 빈 디렉터리 삭제
  <img width="369" height="204" alt="image" src="https://github.com/user-attachments/assets/bdd32f32-2fa3-47f4-baaa-d9bead6ecd62" />

  ### 7. 강제 삭제 옵션 (-f, -rf)
  <img width="432" height="181" alt="image" src="https://github.com/user-attachments/assets/784ca42c-21ec-4441-9f8f-548212066b45" />

  ### 8. 멀티스레딩 기반 다중 파일 삭제
  <img width="440" height="137" alt="image" src="https://github.com/user-attachments/assets/259ff221-15b8-4853-8494-428604fb4864" />

</details>

<details>
  <summary><b>mv - 파일 및 디렉터리 이동 및 이름 변경</b></summary>
  
  ### 1. 초기 디렉터리 구조
  <img width="366" height="225" alt="image" src="https://github.com/user-attachments/assets/8f4be668-8445-410d-86fc-aba94427d4d9" />

  ### 2. 디렉터리 이름 변경
  <img width="371" height="299" alt="image" src="https://github.com/user-attachments/assets/e54c3e75-430b-4384-81ea-f5bbd9d74e22" />

  ### 3. 디렉터리 이동
  <img width="438" height="300" alt="image" src="https://github.com/user-attachments/assets/a87fa27e-f0fb-41b1-a65d-4ec0121de186" />

  ### 4. 파일 이동 및 이름 변경
  <img width="513" height="298" alt="image" src="https://github.com/user-attachments/assets/40ab37bb-fd05-46dc-9cde-4e315c816ba6" />

</details>

<details>
<summary><b>echo - 문자열 출력 및 리다이렉션</b></summary>
  
  ### 1. 파일에 문자열 이어쓰기 (>>)
  <img width="378" height="261" alt="image" src="https://github.com/user-attachments/assets/b76706dd-b67c-4564-a32d-916f8d8c83c3" />

  ### 2. 파일에 문자열 덮어쓰기 (>)
  <img width="482" height="202" alt="image" src="https://github.com/user-attachments/assets/47801af9-f527-4d7b-9670-7f98e8438890" />

  ### 3. 문자열 출력
  <img width="379" height="53" alt="image" src="https://github.com/user-attachments/assets/c5baf10a-3ec2-478c-a084-e8c80e5825cf" />

</details>

## 📁 리포지터리 구조 및 안내
```
miniOS/
├── mv.c
├── rm.c
├── echo.c
└── README.md
```

5인 팀 공동 개발 프로젝트로, 개인 포트폴리오 정리를 위해 본인이 담당한 소스 코드와 프로젝트 구현 내용을 정리하였습니다.  
전체 프로젝트는 Azure VM 환경에서 개발 및 통합되었으며, 본 리포지터리에는 개인 담당 명령어 모듈만 포함되어 있습니다.  
현재 공개된 코드만으로는 전체 Mini OS를 실행할 수 없습니다.
