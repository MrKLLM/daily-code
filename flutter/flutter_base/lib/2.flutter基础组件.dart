import 'package:flutter/material.dart';

void main(List<String> args) {
  runApp(MaterialApp(
      title: "蕾姆赛高",
      theme: ThemeData(
          scaffoldBackgroundColor: const Color.fromARGB(255, 88, 178, 247)),
      home: Scaffold(
        appBar: AppBar(
            title: const Center(
          child: Text("头部区域"),
        )),
        body: Container(
          child: const Center(
            child: Text("中部区域"),
          ),
        ),
        bottomNavigationBar: Container(
          height: 80,
          child: const Center(
            child: Text("底部区域"),
          ),
        ),
      )));
}
