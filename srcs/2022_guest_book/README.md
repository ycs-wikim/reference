# GuestBook
유한대학교 컴퓨터소프트웨어공학과 2022년 학술제에서 사용하기위해 제작한 방명록 프로젝트입니다.

### Made By
* 최우진, 임영기, 이승현, 김선우, 신동화

### Using Language
* C++

### Using IDE
* VC++

### Using Graphic Library
* GDI, GDI+

### Using Naming Convention
* [Google Naming Convention](https://google.github.io/styleguide/cppguide.html#General_Naming_Rules)

### Developer Comment
* 기본적으로 GDI와 GDI+ 그래픽 라이브러리의 경우 특정 작업에서는 하드웨어 가속을 지원하지만 대부분의 작업을 CPU에서 처리합니다.
* GDI+는 GDI의 계량형이지만 그만큼 많은 기능을 제공하고 있기 때문에 상대적으로 처리 속도가 느립니다.<br>
때문에 5배에서 10배꺼지의 속도 차이가 있을 수 있습니다.
* 해당 프로젝트에서는 GDI+를 위주로 작업을 했습니다.<br>
그 이유는 색 선택기를 구현할 때 아래와 같이 두개의 그라디언트를 섞어서 표현을해야 하지만, GDI의 경우 기본적으로 알파값을 지원하지 않기 때문에 GDI+를 위주로 작업했습니다.
![7bc1xkrn0vwv3mb8g5kj](https://user-images.githubusercontent.com/38973547/199628185-6dbf94a8-e34b-4df3-88ed-c2b458e22b1a.jpg)
