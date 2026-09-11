import 'package:flutter/material.dart';

void main(List<String> args) {
  runApp(Mainpage());
}

class Mainpage extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    // TODO: implement build
    return MaterialApp(
      title: "无状态组件",
      theme: ThemeData(scaffoldBackgroundColor: Colors.blue),
      home: Scaffold(
          appBar: AppBar(
              title: Center(
            child: Text("头部"),
          )),
          body: Container(
            child: Center(
              child: Text("中部"),
            ),
          ),
          bottomNavigationBar: Container(
            height: 80,
            child: Center(
              child: Text("底部"),
            ),
          )),
    );
  }
}
