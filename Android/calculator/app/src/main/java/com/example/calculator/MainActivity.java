package com.example.calculator;

import androidx.activity.result.contract.ActivityResultContracts;
import androidx.appcompat.app.ActionBar;
import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Path;
import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.ListAdapter;
import android.widget.TextView;
import android.widget.Toast;

import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.Collections;
import java.util.List;
import java.util.Stack;

public class MainActivity extends AppCompatActivity {

    private TextView txtExpression;
    private TextView txtResult;
    /*  CheckList
        -1 : Equal
         0 : Operator
         1 : Number
         2 : . (dot)
     */
    private List<Integer> checkList;
    private Stack<String> operatorStack;    // Stack for Operator
    private List<String> infixList;         //  Infix notation
    private List<String> postfixList;       //  Postfix notation
    private Stack<String> postStack;    // Stack for Operator

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        this.init();
    }

    void init(){
        txtExpression = findViewById(R.id.txt_expression);
        txtResult = findViewById(R.id.txt_result);
        checkList = new ArrayList<>();
        operatorStack = new Stack<>();
        postStack = new Stack<>();
        infixList = new ArrayList<>();
        postfixList = new ArrayList<>();

//        Todo
        ActionBar actionBar = getSupportActionBar();
        assert actionBar != null;
        actionBar.hide();
    }

//    Event Handling for Number and Operator
    public void buttonClick(View v){
        if(!checkList.isEmpty() && checkList.get(checkList.size()-1)==-1){
            txtExpression.setText(txtResult.getText().toString());
            checkList.clear();
            checkList.add(1);   // Integer
            checkList.add(2);   // . (dot)
            checkList.add(1);   // decimal
            txtResult.setText("");
        }
        switch ((v.getId())){
            case R.id.btn_one : addNumber("1");break;
            case R.id.btn_two : addNumber("2");break;
            case R.id.btn_three : addNumber("3");break;
            case R.id.btn_four : addNumber("4");break;
            case R.id.btn_five : addNumber("5");break;
            case R.id.btn_six : addNumber("6");break;
            case R.id.btn_seven : addNumber("7");break;
            case R.id.btn_eight : addNumber("8");break;
            case R.id.btn_nine : addNumber("9");break;
            case R.id.btn_zero : addNumber("0");break;

            case R.id.btn_dot : addDot(".");break;
            case R.id.btn_division : addOperator("/");break;
            case R.id.btn_multi : addOperator("x");break;
            case R.id.btn_plus : addOperator("+");break;
            case R.id.btn_minus: addOperator("-");break;
//            case R.id.btn_bracket_1: addOperator("(");break;
//            case R.id.btn_bracket_2: addOperator(")");break;

        }
    }

    public void bracketClick(View v){
        Button btn = (Button) findViewById(R.id.btn_bracket);
        btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                checkList.add(0);
                txtExpression.append("( ");
            }
        });

        btn.setOnLongClickListener(new View.OnLongClickListener(){
            @Override
            public boolean onLongClick(View v){
                checkList.add(1);
                txtExpression.append(" )");
                return true;
            }
        });
    }

    public void bracketText(){
        String test = "1+2*(3-4)*5";
//        test.toString().split("\\(" );
        String[] res = test.split("\\(");

        Log.d("3351 ", " "+Arrays.toString(res));
        Log.d("3351 ", " "+res[1]);
    }

    // Event Handling for Clear Button
    public void clearClick(View v){
        infixList.clear();
        postfixList.clear();
        checkList.clear();
        txtExpression.setText("");
        txtResult.setText("");
        operatorStack.clear();
    }

    // Event Handling for delete Button
    public void deleteClick(View v){
//        Log.d("test","3351  "+txtExpression.length());
        if(txtExpression.length()!=0){
            checkList.remove(checkList.size() -1 );
            String[] ex = txtExpression.getText().toString().split(" ");
            List<String> li = new ArrayList<String>();
            Collections.addAll(li, ex);
            li.remove(li.size()-1);
            // 마지막이 연산자일때 " " 빈칸 추가
            if(li.size()>0 && !isNumber(li.get(li.size()-1)))
                li.add(li.remove(li.size()-1)+" ");
            txtExpression.setText(TextUtils.join(" ",li));
        }
        txtResult.setText("");
    }

    public void percentClick(View v){
        double first;
        if(txtExpression.length()==0){
            Toast.makeText(getApplicationContext(),"연산할 숫자가 없습니다.",Toast.LENGTH_SHORT).show();;
            return;
        }else if(txtResult.length()!=0) {
            first = Double.parseDouble(txtResult.getText().toString());
        }else {
            first = Double.parseDouble(txtExpression.getText().toString());
        }
        first *= 0.01;
        String result = String.valueOf(first);
        txtResult.setText(result);
        txtExpression.setText(result);
    }

    // Event Handling for Number Button
    void addNumber(String str){
        checkList.add(1);           // Is Number ?
        txtExpression.append(str);  // UI
    }

    // Event handling for . (dot)
    void addDot(String str) {
        if(checkList.isEmpty()){
            Toast.makeText(getApplicationContext(),". 을 사용할 수 없습니다.",Toast.LENGTH_SHORT).show();;
            return;
        }else if(checkList.get(checkList.size()-1)!=1){
            Toast.makeText(getApplicationContext(),". 을 사용할 수 없습니다.",Toast.LENGTH_SHORT).show();;
            return;
        }
        // 하나의 수에 .(dot)이 여러개 오는것 방지1
        for(int i=checkList.size()-2;i>=0;i--){
            int check = checkList.get(i);
            if(check==2){
                Toast.makeText(getApplicationContext(),". 을 사용할 수 없습니다.",Toast.LENGTH_SHORT).show();;
                return;
            }
            if(check==0)break;
            if(check==1)continue;
        }
        checkList.add(2);
        txtExpression.append(str);
    }

    // Event handling for Operator Button
    void addOperator(String str){
        try{
            if(checkList.isEmpty()){
                Toast.makeText(getApplicationContext(),"연산자가 올 수 없습니다.",Toast.LENGTH_SHORT).show();;
                return;
                // 연산자의 두번 사용 및 완벽한 수가 오지 않음을 방지
            }else if(checkList.get(checkList.size()-1)== 0 && checkList.get(checkList.size()-1)==2){
                Toast.makeText(getApplicationContext(),"연산자가 올 수 없습니다.",Toast.LENGTH_SHORT).show();;
                return;
            }
            checkList.add(0);
            txtExpression.append(" " + str +" ");
        }catch (Exception e){
            Log.e("addOperator",e.toString());
        }
    }

    // Event handling for Equal Button
    public void equalClick(View v){
        if(txtExpression.length()==0) return;
        if(checkList.get(checkList.size()-1)!=1){
            Toast.makeText(getApplicationContext(),"숫자를 제대로 입력해주세요.",Toast.LENGTH_SHORT).show();;
            return;
        }
        Collections.addAll(infixList, txtExpression.getText().toString().split(" "));
        checkList.add(-1);
        for(int i=0;i<infixList.size();i++){
//            Log.d("infixList"," "+infixList.get(i));
        }
//        for(int i=0;i<checkList.size();i++){
//            Log.d("infix List"," "+checkList.get(i));
//        }
        result();
    }

    // Operator weight
    int getWeight(String operator){
        int weight = 0;
        switch (operator) {
            case "x":
            case "/":
                weight = 5;
                break;
            case "(":
            case")":
                weight = 1;
                break;
            case "+":
            case "-":
                weight = 3;
                break;
        }
        return weight;
    }

    boolean isNumber(String str){
        boolean result = true;
        try {
            Double.parseDouble(str);
        }catch (NumberFormatException e){
            result = false;
        }
        return result;
    }
//  original
    // 전위 -> 후위
//    void infixToPostfix(List<String> infixList){
//        for (String item:infixList) {
//            if (isNumber(item))
//                postfixList.add(String.valueOf(Double.parseDouble(item)));
////            else if(item.equals("(")){
////                item = item.replace("(","+");
////                Log.d("iTp"," hello ");
////            }
//            else{
//                if(operatorStack.isEmpty())
//                    operatorStack.push(item);
//                else{
//                    if(getWeight(operatorStack.peek())>=getWeight(item))
//                        postfixList.add(operatorStack.pop());
//                    operatorStack.push(item);
//                }
//            }
//        }
//        while(!operatorStack.isEmpty())
//            postfixList.add(operatorStack.pop());
//    }

    public ArrayList<String> infixToPostfix(List<String> infixList){
        ArrayList<String> result = new ArrayList<>();
        String forPrint="";
        for(int i=0;i<infixList.size();i++){
            switch (infixList.get(i)){
                case "(":
                    postStack.push(infixList.get(i));
                    break;
                case ")":
                    forPrint=postStack.pop();
                    while(!forPrint.equals("(")){
                        result.add(forPrint);
                        forPrint = postStack.pop();
                    }
                    break;
                case"+":
                case"x":
                case"/":
                case"-":
                    while(!postStack.isEmpty() && getWeight(infixList.get(i))<=getWeight(postStack.peek())){
                        forPrint = postStack.pop();
                        result.add(forPrint);
                    }
                    postStack.push(infixList.get(i));
                    break;
                default:
                    result.add(infixList.get(i));
                    break;
            }
        }

        while(!postStack.isEmpty()){
            forPrint=postStack.pop();
            result.add(forPrint);
        }
        Log.d("ITP"," "+result);
        return result;
    }
    // Calculate
    String calculate(String num1, String num2, String op){
        double first = Double.parseDouble(num1);
        double second = Double.parseDouble(num2);
        double result = 0.0;
        try {
            switch (op) {
                case "x":
                    result = first * second;
                    break;
                case "/":
                    result = first / second;
                    break;
                case "+":
                    result = first + second;
                    break;
                case "-":
                    result = first - second;
                    break;
            }
        }catch (Exception e){
            Toast.makeText(getApplicationContext(),"연산할 수 없습니다.",Toast.LENGTH_SHORT).show();
        }
        return String.valueOf(result);
    }


    void result(){
        int i=0;
//        infixToPostfix(infixList);
//        Log.d("infixToPostfix"," "+postfixList);
        ArrayList<String> res = infixToPostfix(infixList);
        Log.d("res ", " "+res);
        Log.d("stack ", " "+postStack); // null
        while(res.size()!=1) {
            if (!isNumber((res.get(i)))) {
                res.add(i - 2, calculate(res.remove(i - 2), res.remove(i - 2), res.remove(i - 2)));
                i = -1;
            }
            i++;
        }

        txtResult.setText(res.remove(0));
        res.clear();
        infixList.clear();

    }


}