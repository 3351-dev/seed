package com.example.androidalarm;

import android.app.AlarmManager;
import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.SharedPreferences;
import android.graphics.Color;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.Switch;
import android.widget.TextView;
import android.widget.ToggleButton;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.google.android.material.floatingactionbutton.FloatingActionButton;

import java.util.List;

public class recyclerAdapter extends RecyclerView.Adapter<recyclerAdapter.ViewHolder> {

    private final List<CardItem> mDataList;
    final Context mContext;
    private RecyclerViewClickListener mListener;
    LinearLayout expandable_view;
    TextView contents_view;
    CheckBox repeat_checkbox;
    private SharedPreferences mPreferences;

    public recyclerAdapter(List<CardItem> DataList, Context context) {
        this.mDataList = DataList;
        this.mContext = context;
    }

    // Click Listener
    public void setOnClickListener(RecyclerViewClickListener listener){
        mListener = listener;
    }

    public interface RecyclerViewClickListener{
        void onItemClicked(int position);
        void onShareButtonClicked(int position);
        void onDeleteButtonClicked(int position);
        void onTitleClicked(int pos);
    }



    @NonNull
    @Override
    // 생성
    public ViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext())
                .inflate(R.layout.item_card, parent, false);

        return new ViewHolder(view);
    }

    @Override
    // 데이터 설정
    public void onBindViewHolder(@NonNull ViewHolder holder, int position) {
        CardItem item = mDataList.get(position);
        holder.title.setText(item.getTitle());
        holder.contents.setText(item.getContents());

        if(mListener != null){
            final int pos = position;
            holder.itemView.setOnClickListener(view -> {
                expandable_view = view.findViewById(R.id.expandable_view);
                contents_view = view.findViewById(R.id.contents_text);
                mListener.onItemClicked(pos);
                if(expandable_view.getVisibility() == View.GONE){
                    expandable_view.setVisibility(View.VISIBLE);
                    contents_view.setVisibility(View.GONE);
//                    Log.d("3351", "unFold " + pos);
//                        Log.d("3351", "repeat btn "+repeat_btn_view.getVisibility());
                }else{
                    expandable_view.setVisibility(View.GONE);
                    contents_view.setVisibility(View.VISIBLE);
//                    Log.d("3351", "Fold "+pos);
//                        Log.d("3351", "repeat btn "+repeat_btn_view.getVisibility());

                }
            });

            holder.share.setOnClickListener(new View.OnClickListener(){

                @Override
                public void onClick(View view) {
                    mListener.onShareButtonClicked(pos);
                }
            });

            holder.delete.setOnClickListener(new View.OnClickListener(){

                @Override
                public void onClick(View view) {
                    mListener.onDeleteButtonClicked(pos);
                }
            });

            holder.repeat.setOnClickListener(new View.OnClickListener(){

                @Override
                public void onClick(View view) {
                    repeat_checkbox = view.findViewById(R.id.repeat_checkbox);
//                    repeat_btn_view = view.findViewById(R.id.repeat_btn_view);    // Question 왜 이렇게 받으면 안되나요
//                    mListener.onRepeatCheckboxClicked(pos);


                    if(repeat_checkbox.isChecked()){
                        Log.d("3351","Checked " + pos );
                        holder.repeat_view.setVisibility(View.VISIBLE);
                        // repeat init
                        holder.sun.setChecked(true);
                    }else{
                        holder.repeat_view.setVisibility(View.GONE);
                    }
                }

            });

            holder.OnOff.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    if(holder.OnOff.isChecked()){
                        String str;
                        mPreferences = mContext.getSharedPreferences("alarm",Context.MODE_PRIVATE);
                        str = mPreferences.getString(String.valueOf(0),"");

                        String[] time = str.split(":");
                        /*mAlarmManager.setExact(AlarmManager.RTC_WAKEUP,calendar.getTimeInMillis(),operation);*/

                        Log.d("OnOff"," ON "+str+" "+time[0] + " "+time[1]);
                        holder.title.setTextColor(Color.BLUE);
                        holder.contents.setTextColor(Color.BLUE);
                    }else{
                        Log.d("OnOff"," OFF "+pos);
                        holder.title.setTextColor(Color.BLACK);
                        holder.contents.setTextColor(Color.BLACK);
                    }

                }
            });

            holder.title.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
//                    Log.d("adapter","setText : "+holder.title.getText());
                    mListener.onTitleClicked(pos);
                }
            });

        }

    }

    @Override
    // 아이템 갯수
    public int getItemCount() {
        return mDataList.size();
    }

    // 각 아이템의 레퍼런스를 저장할 뷰 홀더 클래스
    // 반드시 RecyclerView.ViewHolder를 상속해야함
    public static class ViewHolder extends RecyclerView.ViewHolder{
        Button delete;
        Button share;
        Switch OnOff;
        CheckBox repeat;
        TextView title;
        TextView contents;
        LinearLayout repeat_view;
        ToggleButton mon;
        ToggleButton tue;
        ToggleButton wed;
        ToggleButton thu;
        ToggleButton fri;
        ToggleButton sat;
        ToggleButton sun;
        TextView label_view;
        TextView contents_view;


        public ViewHolder(View itemView) {
            super(itemView);
            title = (TextView) itemView.findViewById(R.id.title_text);
            contents = (TextView) itemView.findViewById(R.id.contents_text);
            delete = (Button) itemView.findViewById(R.id.delete_button);
            share = (Button) itemView.findViewById(R.id.add_button);
            repeat = (CheckBox) itemView.findViewById(R.id.repeat_checkbox);
            repeat_view = (LinearLayout) itemView.findViewById(R.id.repeat_btn_view);
            OnOff = (Switch) itemView.findViewById(R.id.OnOff_btn);
            label_view = (TextView)itemView.findViewById(R.id.label_view);


            mon = (ToggleButton) itemView.findViewById(R.id.mon_btn);
            tue = (ToggleButton) itemView.findViewById(R.id.tue_btn);
            wed = (ToggleButton) itemView.findViewById(R.id.wed_btn);
            thu = (ToggleButton) itemView.findViewById(R.id.thu_btn);
            fri = (ToggleButton) itemView.findViewById(R.id.fri_btn);
            sat = (ToggleButton) itemView.findViewById(R.id.sat_btn);
            sun = (ToggleButton) itemView.findViewById(R.id.sun_btn);

            mon.setOnCheckedChangeListener((compoundButton, b) -> {
                if(b){
                    Log.d("toggle","on");
                    b = true;
                }else{
                    Log.d("toggle","off");
                    b = false;
                }
                {
                    if (!sun.isChecked() && !mon.isChecked()
                            && !tue.isChecked() && !wed.isChecked()
                            && !thu.isChecked() && !fri.isChecked()
                            && !sat.isChecked()){
                        Log.d(" ", "repeat off");
                        repeat.setChecked(false);
                        repeat_view.setVisibility(View.GONE);
                    }
                }
            });
            tue.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
                @Override
                public void onCheckedChanged(CompoundButton compoundButton, boolean b) {
                    if(b){
                        Log.d("toggle","on");
                        b = true;
                    }else{
                        Log.d("toggle","off");
                        b = false;
                    }
                    {
                        if (!sun.isChecked() && !mon.isChecked()
                                && !tue.isChecked() && !wed.isChecked()
                                && !thu.isChecked() && !fri.isChecked()
                                && !sat.isChecked()){
                            Log.d(" ", "repeat off");
                            repeat.setChecked(false);
                            repeat_view.setVisibility(View.GONE);
                        }
                    }
                }
            });
            wed.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
                @Override
                public void onCheckedChanged(CompoundButton compoundButton, boolean b) {
                    if(b){
                        Log.d("toggle","on");
                        b = true;
                    }else{
                        Log.d("toggle","off");
                        b = false;
                    }
                    {
                        if (!sun.isChecked() && !mon.isChecked()
                                && !tue.isChecked() && !wed.isChecked()
                                && !thu.isChecked() && !fri.isChecked()
                                && !sat.isChecked()){
                            Log.d(" ", "repeat off");
                            repeat.setChecked(false);
                            repeat_view.setVisibility(View.GONE);
                        }
                    }
                }
            });
            thu.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
                @Override
                public void onCheckedChanged(CompoundButton compoundButton, boolean b) {
                    if (b) {
                        Log.d("toggle", "on");
                        b = true;
                    } else {
                        Log.d("toggle", "off");
                        b = false;
                    }
                    {
                        if (!sun.isChecked() && !mon.isChecked()
                                && !tue.isChecked() && !wed.isChecked()
                                && !thu.isChecked() && !fri.isChecked()
                                && !sat.isChecked()){
                            Log.d(" ", "repeat off");
                            repeat.setChecked(false);
                            repeat_view.setVisibility(View.GONE);
                        }
                    }
                }

            });
            fri.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
                @Override
                public void onCheckedChanged(CompoundButton compoundButton, boolean b) {
                    if(b){
                        Log.d("toggle","on");
                        b = true;
                    }else{
                        Log.d("toggle","off");
                        b = false;
                    }
                    {
                        if (!sun.isChecked() && !mon.isChecked()
                                && !tue.isChecked() && !wed.isChecked()
                                && !thu.isChecked() && !fri.isChecked()
                                && !sat.isChecked()){
                            Log.d(" ", "repeat off");
                            repeat.setChecked(false);
                            repeat_view.setVisibility(View.GONE);
                        }
                    }
                }

            });
            sat.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
                @Override
                public void onCheckedChanged(CompoundButton compoundButton, boolean b) {
                    if(b){
                        Log.d("toggle","on");
                        b = true;
                    }else{
                        Log.d("toggle","off");
                        b = false;
                    }
                    {
                        if (!sun.isChecked() && !mon.isChecked()
                                && !tue.isChecked() && !wed.isChecked()
                                && !thu.isChecked() && !fri.isChecked()
                                && !sat.isChecked()){
                            Log.d(" ", "repeat off");
                            repeat.setChecked(false);
                            repeat_view.setVisibility(View.GONE);
                        }
                    }
                }

            });
            sun.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
                @Override
                public void onCheckedChanged(CompoundButton compoundButton, boolean b) {
                    if(b){
                        Log.d("toggle","on");
                        b = true;
                    }else{
                        Log.d("toggle","off");
                        b = false;
                    }
                    {
                        if (!sun.isChecked() && !mon.isChecked()
                                && !tue.isChecked() && !wed.isChecked()
                                && !thu.isChecked() && !fri.isChecked()
                                && !sat.isChecked()){
                            Log.d(" ", "repeat off");
                            repeat.setChecked(false);
                            repeat_view.setVisibility(View.GONE);
                        }
                    }
                }

            });
            label_view.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    AlertDialog.Builder alert = new AlertDialog.Builder(view.getContext());
                    alert.setTitle("Label");

                    final EditText usercontents = new EditText(view.getContext());
                    alert.setView(usercontents);

                    alert.setPositiveButton("ok", new DialogInterface.OnClickListener() {
                        @Override
                        public void onClick(DialogInterface dialogInterface, int i) {
                            String userContents = usercontents.getText().toString();
                            contents.setText(userContents);
                            Log.d("AlertDialog"," "+userContents);
                        }
                    });
                    alert.show();
                }
            });


        }

    }
    //  애니메이션 추가
    public void removeItem(int position){
        mDataList.remove(position);
        notifyItemRemoved(position);
        notifyItemRangeChanged(position,mDataList.size());
    }
    public void addItem(int position, CardItem item){
        mDataList.add(position, item);
        notifyItemInserted(position);
        notifyItemRangeChanged(position, mDataList.size());
    }


}
