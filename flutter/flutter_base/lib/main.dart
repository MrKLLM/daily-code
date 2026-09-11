import 'package:flutter/material.dart';

void main(List<String> args) {
  // runApp(Mainpage());
  runApp(MainPage());
}

// class Mainpage extends StatelessWidget {
//   @override
//   Widget build(BuildContext context) {
//     // TODO: implement build
//     return MaterialApp(
//       title: "无状态组件",
//       theme: ThemeData(scaffoldBackgroundColor: Colors.blue),
//       home: Scaffold(
//           appBar: AppBar(
//               title: Center(
//             child: Text("头部"),
//           )),
//           body: Container(
//             child: Center(
//               child: Text("中部"),
//             ),
//           ),
//           bottomNavigationBar: Container(
//             height: 80,
//             child: Center(
//               child: Text("底部"),
//             ),
//           )),
//     );
//   }
// }

//有状态组件吧 第一个类
class MainPage extends StatefulWidget {
  @override
  State<StatefulWidget> createState() {
    // TODO: implement createState
    // return 第二个类的对象
    return _MainPageState();
  }
}

//第二个类 内部类 负责管理数据 处理业务数据 并且渲染视图
class _MainPageState extends State<MainPage> {
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
