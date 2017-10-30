package com.example.seray.mantaryetistirme7mart;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageButton;

public class KontrolActivity extends AppCompatActivity {

    Button buton5;
    ImageButton buton2, buton3;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_kontrol);





        buton2=(ImageButton)findViewById(R.id.id_button_otomatikkontrol);


        buton2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent=new Intent(KontrolActivity.this, OtomatikKontrolActivity.class);
                startActivity(intent);
            }
        });

        buton3=(ImageButton)findViewById(R.id.id_button_ozel_kontrol);


        buton3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent=new Intent(KontrolActivity.this, OzelKontrolActivity.class);
                startActivity(intent);
            }
        });






    }
}
