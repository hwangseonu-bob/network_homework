# netfilter_test

iptables와 netfilter 라이브러리를 활용하여 denylist를 구현한다.

## iptables

기본적으로 규칙을 추가하는 명령어 구성은 다음과 같다.
`iptables -A INPUT -s [source ip] --sport [source port] -d [destination ip] --dport [destination port] -j [policy] `

`-A`옵션은 맨 뒤에 추가되는 `--append`옵션이며  
`-I`옵션은 맨 앞에 추가되는 `--insert`옵션이다.

정책(policy)에는 ACCEPT, DROP, REJECT, QUEUE 등이 있으며  
`netfilter queue`에서 패킷을 받아 처리하기 위해서는 QUEUE 정책을 사용한다.

`iptables --list` 또는 `iptables -L` 명령어를 통해 현재의 iptables 규칙을 볼 수 있다.

`iptables -F` 명령어로 현재의 iptables 규칙을 초기화 할 수 있다.

자세한 사용방법은 `man` 명령어를 통해 확인하도록 한다.

## netfilter

iptables에서 QUEUE로 보낸 패킷은 `netfilter queue` 라이브러리를 통해 처리할 수 있다.

사용방법은 [코드](./src/main.cpp) 참고

## build

>> cd netfilter_test

>> cmake .

>> cmake --build .
