# OmulOmulVigilante
[![Video Label](http://img.youtube.com/vi/v83PVF8onCI/0.jpg)](https://youtu.be/v83PVF8onCI)
[![Video Label](http://img.youtube.com/vi/6tIn7lAkAwc/0.jpg)](https://youtu.be/6tIn7lAkAwc)

## 프로젝트 소개
- 오물 풍선이 날라오는 가상환경에서 행동을 LLM이 파악하고 평가하는 시뮬레이션


## 목적
- 북한에서 날아오는 오물 풍선 재난에 대해 민간 차원에서도 대처 훈련이 필요하다.
- 실제로 일어날 수 있는 재난을 가상의 세계에서 경험하면서 갑작스러운 상황을 대처하는 능력 향상
- 인증 수료 시스템을 통한 안보 교육 시스템 개발

## 기능
- 로그인/회원가입
- 음성으로 112 신고하는 시뮬레이션
- 오물풍선 근처로 다가가지 않도록 거리 측정 시뮬레이션
- 주변 사람에게 다가가지 말라고 알리는 시뮬레이션
- 점수 산출 시스템
- 점수 기록 및 수료증 발급 시스템

## RAG 
### 데이터 셋
- 오물풍선 처리 메뉴얼 및 인터뷰에서 기반한 자체 제작 text파일
### 프롬프트
#### 언어
- 한국어
#### 병렬 연결 
- RAG Prompt
- System Prompt

## 모델 
### gpt-4o-mini
### whisper-large-v3

## 서버
### 서버 -> Fast API
- Post Header Token for username
- Post AverDistance
- Post Alerted
### Fast API -> 서버
- Post Header Token for username
- Post Score
- Post Reason

## 실행파일
### [다운로드](https://drive.google.com/file/d/1PZziY7vE6ZT4DewuusGCFH7G_8YGeQZn/view?usp=sharing)