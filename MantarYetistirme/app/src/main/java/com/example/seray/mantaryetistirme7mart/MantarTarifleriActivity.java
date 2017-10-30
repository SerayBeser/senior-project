package com.example.seray.mantaryetistirme7mart;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageButton;

public class MantarTarifleriActivity extends AppCompatActivity {

    ImageButton buton1,buton2,buton3,buton4,buton5,buton6,buton7,buton8,buton9,buton10;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_mantar_tarifleri);

        ImageButton buton1=(ImageButton)findViewById(R.id.id_imageButton_corba);

        ImageButton buton2=(ImageButton)findViewById(R.id.id_imageButton_graten);
        ImageButton buton3=(ImageButton)findViewById(R.id.id_imageButton_volovan);
        ImageButton buton4=(ImageButton)findViewById(R.id.id_imageButton_pilav);
        ImageButton buton5=(ImageButton)findViewById(R.id.id_imageButton_makarna);
        ImageButton buton6=(ImageButton)findViewById(R.id.id_imageButton_dolma);
        ImageButton buton7=(ImageButton)findViewById(R.id.id_imageButton_patates);
        ImageButton buton8=(ImageButton)findViewById(R.id.id_imageButton_salata);
        ImageButton buton9=(ImageButton)findViewById(R.id.id_imageButton_tartolet);
        ImageButton buton10=(ImageButton)findViewById(R.id.id_imageButton_guvec);


        buton1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent=new Intent(MantarTarifleriActivity.this, YemekTarifi1Activity.class);
                startActivity(intent);
            }
        });

        buton2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent=new Intent(MantarTarifleriActivity.this, YemekTarifi2Activity.class);
                startActivity(intent);
            }
        });
        buton3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent=new Intent(MantarTarifleriActivity.this, YemekTarifi3Activity.class);
                startActivity(intent);
            }
        });
        buton4.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent=new Intent(MantarTarifleriActivity.this, YemekTarifi4Activity.class);
                startActivity(intent);
            }
        });
        buton5.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent=new Intent(MantarTarifleriActivity.this, YemekTarifi5Activity.class);
                startActivity(intent);
            }
        });
        buton6.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent=new Intent(MantarTarifleriActivity.this, YemekTarifi6Activity.class);
                startActivity(intent);
            }
        });
        buton7.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent=new Intent(MantarTarifleriActivity.this, YemekTarifi7Activity.class);
                startActivity(intent);
            }
        });
        buton8.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent=new Intent(MantarTarifleriActivity.this, YemekTarifi8Activity.class);
                startActivity(intent);
            }
        });


        buton9.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent=new Intent(MantarTarifleriActivity.this, YemekTarifi9Activity.class);
                startActivity(intent);
            }
        });

        buton10.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent=new Intent(MantarTarifleriActivity.this, YemekTarifi10Activity.class);
                startActivity(intent);
            }
        });




    }
}
