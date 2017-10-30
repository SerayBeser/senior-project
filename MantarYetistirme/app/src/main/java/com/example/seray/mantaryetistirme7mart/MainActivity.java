package com.example.seray.mantaryetistirme7mart;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageButton;

public class MainActivity extends AppCompatActivity {


    ImageButton buton1,buton2,buton3,buton4;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        buton1=(ImageButton)findViewById(R.id.id_imageButton_ayarlar);


        buton1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent=new Intent(MainActivity.this, AyarlarActivity.class);
                startActivity(intent);
            }
        });


        buton2=(ImageButton)findViewById(R.id.id_imageButton_mantarsecimi);


        buton2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
               Intent intent=new Intent(MainActivity.this, MantarSecimiActivity.class);
               startActivity(intent);
            }
        });

        buton3=(ImageButton)findViewById(R.id.id_imageButton_mantarbilg);


        buton3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent=new Intent(MainActivity.this, MantarBilgileriActivity.class);
                startActivity(intent);
            }
        });
        buton4=(ImageButton)findViewById(R.id.id_imageButton_mantartarif);


        buton4.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent=new Intent(MainActivity.this, MantarTarifleriActivity.class);
                startActivity(intent);
            }
        });

    }





}
