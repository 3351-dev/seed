# RecyclerViewText   

### 종속항목 선언   
* build.gradle(:app)의 dependencies에 종속항목 선언   
	implementation("androidx.recyclerview:recyclerview:1.2.1")   
* developer.android.com/jetpack

### RecyclerViewAdapter   
* onCreateViewHolder   
	최초에 레이아웃을 생성하고 뷰 홀더에 보관하는 부분   
* onBindViewHolder   
	홀더에 데이터를 설정하는 부분   
* getItemCount   
	아이템의 갯수   
