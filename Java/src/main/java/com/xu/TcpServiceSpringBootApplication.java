package com.xu;

import com.xu.javaFx.view.ServerView;
import de.felixroske.jfxsupport.AbstractJavaFxApplicationSupport;
import javafx.event.EventHandler;
import javafx.scene.image.Image;
import javafx.stage.Stage;
import javafx.stage.WindowEvent;

import org.springframework.boot.autoconfigure.SpringBootApplication;


@SpringBootApplication
public class TcpServiceSpringBootApplication extends AbstractJavaFxApplicationSupport {
	@Override
	public void start(Stage stage) throws Exception {
		super.start(stage);
		stage.setTitle("徐菜鸟的Tcp服务端");
		stage.getIcons().add(new Image("/1.ico"));
		stage.setResizable(true);
		stage.setOnCloseRequest(new EventHandler<WindowEvent>() {
			@Override
			public void handle(WindowEvent event) {
				System.exit(0);
			}
		});
	}
	public static void main(String[] args) {
		launch(TcpServiceSpringBootApplication.class, ServerView.class,args);
	}

}
