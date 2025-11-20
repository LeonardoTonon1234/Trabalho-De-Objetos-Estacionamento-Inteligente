package com.estacionamento.api;

import org.springframework.boot.CommandLineRunner;
import org.springframework.stereotype.Component;

@Component
public class DataLoader implements CommandLineRunner {

    private final VagaRepository vagaRepository;

    public DataLoader(VagaRepository vagaRepository) {
        this.vagaRepository = vagaRepository;
    }

    @Override
    public void run(String... args) throws Exception {
        // Criar vagas iniciais
        Vaga v1 = new Vaga("A1", "LIVRE");
        Vaga v2 = new Vaga("A2", "OCUPADA");
        Vaga v3 = new Vaga("A3", "LIVRE");

        vagaRepository.save(v1);
        vagaRepository.save(v2);
        vagaRepository.save(v3);

        System.out.println("✔ Vagas carregadas automaticamente no H2!");
    }
}
