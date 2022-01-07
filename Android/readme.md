# androidAlarm
### Android Animation   
* https://fornewid.medium.com/android-ui%EC%97%90-animation-%EB%93%A4%EC%9D%B4%EB%B6%93%EA%B8%B0-e95cabbb517c   

### TabLayout   
* https://ju-hy.tistory.com/54   

## 1229~1230

### Title 클릭시 Folding/Unfolding
   
* LinearLayout에 Visibility 추가

### 참고 블로그   
* https://parkho79.tistory.com/152?category=798724   

### Repeat 클릭시 요일 출력   

* Repeat checkbox   

### 요일 클릭시 background 전환   

* ToggleButton   

### Swich를 통한 Title, contents 색상 변경

* setTextColor   
![Screenshot from 2021-12-30 18-02-10](https://user-images.githubusercontent.com/93642972/147738012-3f5f04d6-c48b-4095-94df-fda5b4538b1b.png)
![Screenshot from 2021-12-30 18-06-30](https://user-images.githubusercontent.com/93642972/147738087-bba4f1f2-c85a-454b-90ac-e6f37ca29c8a.png)

## 1231

### AlertDialog

* https://answerofgod.tistory.com/83

## 0103

### Timepicker ADD   
* Error   
	* getSupportFragmentManager : Fragment Activity의 메소드   
	* ViewHolder에서 구현하려고 하니 잘 되지 않네요..   
	
## 0104

### Timepicker ADD
* recyclerAdapter에서 fragment_view_1에서 처리하도록 넘겨주었다.      
	private FragmentActivity myContext;   
	선언 후 밑 구문 추가   
	   		   
	@Override   
	public void onAttach(Activity activity){   
		myContext = (FragmentActivity) activity;   
		super.onAttach(activity);   
	}      
	이후 클릭했을때 이벤트 출력   
	FragmentManager fragmentManager = myContext.getSupportFragmentManager();   
	   
* 참고   
	http://daplus.net/android-%ED%94%84%EB%9E%98%EA%B7%B8%EB%A8%BC%ED%8A%B8%EC%97%90%EC%84%9C-getsupportfragmentmanager-%EC%97%90-%EC%96%B4%EB%96%BB%EA%B2%8C-%EC%95%A1%EC%84%B8%EC%8A%A4-%ED%95%A0-%EC%88%98-%EC%9E%88/   
	
## 0105

### Fragment ~ Fragment 값 전달   
* Intent : 데이터를 전달   	
* Bundle : 데이터를 저장   
* Bundle을 이용해서 값 반환   
* https://fjdkslvn.tistory.com/14   

### SharedPerference
* 다음 두가지 모두 사용가능
	* preference = PreferenceManager.getDefaultSharedPreferences(this);   
	* preference = getSharedPreferences("FileName", MODE);   
		* mode : MODE_PRIVATE, MODE_WORLD_READABLE, MODE_WORD_WRITEABLE   
SharedPreferences.Editor editor = preferences.edit();   
editor.putString("key",value);   
editor.commit()   
getPreferences();   

## 0106

Bundle을 이용하여 Fragment_view_1과 TimePickerFragment 사이 값 전달    
* AlarmManager   
```
Intent intent = new Intent(getContext(), alaramReceiver.class);   
PendingIntent operation = PendingIntent.getBroadcast(getContext(),0,intent,0);
mAlarmManager.set(AlarmManager.RTC_WAKEUP, calendar.getTimeInMillis(), operation);
```
	
* 정각에 알리게끔 수정할것   

## 0107

setExact를 통해 정각에 시간을 알리도록 설정   
! calendar.set(Calendar.SECOND, 0)으로 설정하여 정각 0초에 알리도록 설정해야함   
+ https://greedy0110.tistory.com/69   
   
* 중간에 있는 값을 삭제하고 List와 Preferences가 일치하지않는 문제   
```
for(After){
	if(mPreferences(i)=""){
		for(before){
			if(mPreferences(j)=""){
				mPreferences.put(j+1);   
				mPreferences.remove(j+1);   
				mPreferences.apply();
			}
		}
	}
}
```
   
* 
