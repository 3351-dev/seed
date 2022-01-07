package com.example.first;

import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.ResourceManagerInternal;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {
    TextView et_show, et_result;
    Button plus, minus, mul, div, del, remainder, trans, clear ;
    Button result;

    String history ="";
    String number1="";
    String number2="";

    int type;

    int PLUS=1;
    int MINUS=2;
    int MUL=3;
    int DIV=4;
    int REMAINDER =5;
    int TRANS = 6;
    int DEL = 7;

    double d1;
    double d2;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

//        connect xml ~ java
        et_show = findViewById(R.id.view_exp);
        et_result=findViewById(R.id.view_res);
        et_result.setText("");
        plus = findViewById(R.id.btn_plus);
        minus = findViewById(R.id.btn_minus);
        mul = findViewById(R.id.btn_multiple);
        div = findViewById(R.id.btn_division);
        remainder = findViewById(R.id.btn_remainder);
        clear = findViewById(R.id.btn_ac);
        del = findViewById(R.id.btn_del);
        trans = findViewById(R.id.btn_trans);

        result = findViewById(R.id.btn_res);

//        add Listener
        plus.setOnClickListener(mListener);
        minus.setOnClickListener(mListener);
        mul.setOnClickListener(mListener);
        div.setOnClickListener(mListener);
        remainder.setOnClickListener(mListener);
        result.setOnClickListener(mListener);
        del.setOnClickListener(mListener);

//        init
        Button clear = findViewById(R.id.btn_ac);
        clear.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v){
                et_show.setText("");
                et_result.setText("");
                d1=d2=0;
                history=number1=number2="";
            }
        });
        Button trans=findViewById(R.id.btn_trans);
        trans.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v){
                if(((Double.parseDouble(et_result.getText().toString()))-(int)Double.parseDouble(et_result.getText().toString())) ==0.0 ){
                    et_result.setText("" + (Integer.parseInt(et_result.getText().toString())*-1));
                }else{
                    et_result.setText(""+(Double.parseDouble(et_result.getText().toString())*-1));
                }
            }
        });
    }

    Button.OnClickListener mListener = new Button.OnClickListener() {
        @Override
        public void onClick(View v) {
            if (et_result.getText().toString() == null) {
                Toast.makeText(MainActivity.this, "Number input plz", Toast.LENGTH_SHORT).show();
            }
            switch (v.getId()) {
                case R.id.btn_plus:
                    number1 = et_result.getText().toString();
                    history = et_result.getText().toString() + " + ";
                    et_show.setText(history);
                    et_result.setText("");
                    type = PLUS;
                    break;

                case R.id.btn_minus:
                    number1 = et_result.getText().toString();
                    history = et_result.getText().toString() + " - ";
                    et_show.setText(history);
                    et_result.setText("");
                    type = MINUS;
                    break;

                case R.id.btn_multiple:
                    number1 = et_result.getText().toString();
                    history = et_result.getText().toString() + " * ";
                    et_show.setText(history);
                    et_result.setText("");
                    type = MUL;
                    break;

                case R.id.btn_division:
                    number1 = et_result.getText().toString();
                    history = et_result.getText().toString() + " / ";
                    et_show.setText(history);
                    et_result.setText("");
                    type = DIV;
                    break;

                case R.id.btn_remainder:
                    number1 = et_result.getText().toString();
                    history = et_result.getText().toString() + " % ";
                    et_show.setText(history);
                    et_result.setText("");
                    type = REMAINDER;
                    break;

                case R.id.btn_del:
                    String del_number = et_result.getText().toString();
                    et_result.setText(del_number.substring(0,del_number.length()-1));
                    break;

                case R.id.btn_res:
                    double result = 0;
                    Toast.makeText(MainActivity.this, "res", Toast.LENGTH_SHORT).show();
                    number2 = et_result.getText().toString();
//                    history = et_result.getText().toString();
//                    history = history + et_result.getText().toString();
                    history += number2;
                    et_show.setText(history);

                    d1 = Double.parseDouble(number1);
                    d2 = Double.parseDouble(number2);

                    if (type == PLUS) {
                        result = d1 + d2;
                        et_result.setText("" + result);
                    } else if (type == MINUS) {
                        result = d1 - d2;
                        et_result.setText("" + result);
                    } else if (type == MUL) {
                        result = d1 * d2;
                        et_result.setText("" + result);
                    } else if (type == DIV) {
                        result = d1 / d2;
                        et_result.setText("" + result);
                    } else if (type == REMAINDER) {
                        result = d1 % d2;
                        et_result.setText("" + result);
                    }

                    number1 = et_result.getText().toString();
                    break;
            }
        }
    };
    public void onClick(View v){
        switch(v.getId()){
            case R.id.btn_num0 : et_result.setText(et_result.getText().toString()+0);break;
            case R.id.btn_num1 : et_result.setText(et_result.getText().toString()+1);break;
            case R.id.btn_num2 : et_result.setText(et_result.getText().toString()+2);break;
            case R.id.btn_num3 : et_result.setText(et_result.getText().toString()+3);break;
            case R.id.btn_num4 : et_result.setText(et_result.getText().toString()+4);break;
            case R.id.btn_num5 : et_result.setText(et_result.getText().toString()+5);break;
            case R.id.btn_num6 : et_result.setText(et_result.getText().toString()+6);break;
            case R.id.btn_num7 : et_result.setText(et_result.getText().toString()+7);break;
            case R.id.btn_num8 : et_result.setText(et_result.getText().toString()+8);break;
            case R.id.btn_num9 : et_result.setText(et_result.getText().toString()+9);break;
            case R.id.btn_dot : et_result.setText(et_result.getText().toString()+".");break;


        }
    }

}