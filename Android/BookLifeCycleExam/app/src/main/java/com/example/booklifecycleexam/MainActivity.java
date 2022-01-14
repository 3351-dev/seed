package com.example.booklifecycleexam;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    private TextView mLevelText;
    private TextView mScoreText;
    private int mLevel = 0;
    private int mScore = 0;
    static final String STATE_SCORE = "playerScore";
    static final String STATE_LEVEL = "playerLevel";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mLevelText = (TextView) findViewById(R.id.level_text);
        mScoreText = (TextView) findViewById(R.id.score_text);
        if(savedInstanceState == null){
            // 초기화할 코드
        }else{
            // 상태 복원 방법 1; 설정해주지 않으면 화면전환시 데이터를 저장하지않는다
            /*mLevel = savedInstanceState.getInt(STATE_LEVEL);
            mScore = savedInstanceState.getInt(STATE_SCORE);
            mLevelText.setText("Level "+mLevel);
            mScoreText.setText("Point "+mScore);*/
        }
    }

    public void onLevelUp(View view) {
        mLevel++;
        mLevelText.setText("Level "+mLevel);
    }

    public void onScoreUp(View view) {
        mScore+=100;
        mScoreText.setText("Point "+mScore);
    }

    @Override
    protected void onSaveInstanceState(Bundle outState) {
        // 상태 저장
        outState.putInt(STATE_SCORE, mScore);
        outState.putInt(STATE_LEVEL, mLevel);

        super.onSaveInstanceState(outState);
    }

    // 상태 복원 방법 2
    protected void onRestoreInstanceState(Bundle savedInstanceState){
        super.onRestoreInstanceState(savedInstanceState);
        // 상태 복원
        mLevel = savedInstanceState.getInt(STATE_LEVEL);
        mScore = savedInstanceState.getInt(STATE_SCORE);
        mLevelText.setText("Level "+mLevel);
        mScoreText.setText("Score "+mScore);
    }
}