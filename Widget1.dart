import 'package:flutter/material.dart';

void main() => runApp(MyApp());

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    // TODO: implement build
    return MaterialApp(
      title: 'Charactor Cart',
      home: Mycard(),
    );
  }
}

class Mycard extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    // TODO: implement build
    return Scaffold(
      appBar: AppBar(
          title: Text('BBanto'),
          centerTitle: true, // appBar 정렬 true, false
          backgroundColor: Colors.redAccent, // appBar 배경색
          elevation: 0.0 // appBar의 그림자(수치화)
          ),
      body: Center( // Center은 body 정 중앙이 아니라 세로배열 중앙
        // body에서 위젯 위치조정
        child: Column(  //세로정렬
          mainAxisAlignment: MainAxisAlignment.center ,  // 가로 상단, 중단, 하단으로 정렬
          children: <Widget>[
            Text('Hello'),
            Text('Hello'),
            Text('Hello')
          ]
        )
      )
    );
  }
}
